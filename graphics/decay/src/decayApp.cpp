#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/params/Params.h"
#include "cinder/Camera.h"

#include "world.h"
#include "rule.h"
#include "ogl.h"
#include "osc.h"

#include <sstream>

using namespace ci;
using namespace ci::app;
using namespace std;

#define DELIM ','

class decayApp : public AppBasic {
  public:
	void prepareSettings( Settings *settings );
	void setup();
	void resize( ResizeEvent event );
	void update();
	void draw();
	void shutdown();

	CameraPersp mCam;	
	Matrix44f mRotation;
	
	Vec3f mEye, mCenter, mUp;
	params::InterfaceGl mParams;
	
	float mDirectional;
	Vec2f mMousePos;
	
  private:
	World *_world;
	Rule *_rule;
	GraphicsRenderer *_ogl;
	OSCMessenger *_oscMessenger;
	int *_births, *_survivals, _states;
	
	int _winSizeX, _winSizeY, _worldSizeX, _worldSizeY, _worldSizeZ, _inport, _outport;
	float _frameRate;
	string _remoteHost;
	
	void getBirthsFromArg(const string &s);
	void getSurvivalsFromArg(const string &s);
	
};

void decayApp::prepareSettings(Settings *settings) {

	vector<string> args;
	int i;
	string myarg;
	
	args = getArgs();
	
	for (i = 1; i < args.size(); i+=2) {
		if (args[i].compare("-screenx") == 0) {
			_winSizeX = atoi(args[i+1].c_str());
		}
		else if (args[i].compare("-screeny") == 0) {
			_winSizeY = atoi(args[i+1].c_str());		
		}
		else if (args[i].compare("-worldx") == 0) {
			_worldSizeX = atoi(args[i+1].c_str());		
		}
		else if (args[i].compare("-worldy") == 0) {
			_worldSizeY = atoi(args[i+1].c_str());		
		}
		else if (args[i].compare("-worldz") == 0) {
			_worldSizeZ = atoi(args[i+1].c_str());		
		}
		else if (args[i].compare("-births") == 0) {
			getBirthsFromArg(args[i+1]);
		}
		else if (args[i].compare("-survivals") == 0) {
			getSurvivalsFromArg(args[i+1]);
		}
		else if (args[i].compare("-states") == 0) {
			_states = atoi(args[i+1].c_str());		
		}		
		else if (args[i].compare("-fps") == 0) {
			_frameRate = atof(args[i+1].c_str());		
		}
		else if (args[i].compare("-remote") == 0) {
			_remoteHost = args[i+1];		
		}
		else if (args[i].compare("-inport") == 0) {
			_inport = atoi(args[i+1].c_str());		
		}
		else if (args[i].compare("-outport") == 0) {
			_outport = atoi(args[i+1].c_str());		
		}
	}	
	
	settings->setWindowSize( _winSizeX, _winSizeY );
	settings->setFrameRate( _frameRate );
}

void decayApp::setup()
{
	
	_world = new World(_worldSizeX, _worldSizeY, _worldSizeZ);
//	_world->initWireCube(5, 5, 5, 19, 19, 19);
//	_world->initRandInArea(4, 4, 4, _worldSizeX - 5, _worldSizeY - 5, _worldSizeZ - 5, _states - 1, 0.8);
	_rule = new Faders(_births, _survivals, _states);
	
	_ogl = new GraphicsRenderer();
	_ogl->setupOgl(0, 0, _worldSizeX, _worldSizeY, _worldSizeZ );
	_oscMessenger = new OSCMessenger(_remoteHost, _outport, _inport, _world, _ogl, _rule);
		
	mEye = Vec3f(0.0f, 0.0f, -35.0f);
	mCenter = Vec3f::zero();
	mUp = Vec3f::yAxis();
	
	mCam.lookAt(mEye, mCenter, mUp);
	mRotation.setToIdentity();
		
	gl::enableDepthRead();
	gl::enableDepthWrite();		
	gl::enableAlphaBlending();
	
}

void decayApp::resize(ResizeEvent event) {
	mCam.setPerspective(45.0, getWindowAspectRatio(), 1.0f, 1000.0f);
	gl::setMatrices( mCam );	
}

void decayApp::shutdown()
{
	delete [] _births;
	delete [] _survivals;
	delete _rule;
	delete _world;
	delete _oscMessenger;
	delete _ogl;
}

void decayApp::update() 
{
	if (_oscMessenger->quit()) { quit(); }
	
	mRotation.rotate( Vec3f( 0.0f, 1.0f, 0.0f ), 0.005f );
		
	gl::clear( Color(0, 0, 0), true);
	_ogl->setupFrame(_world->index(), _rule->numStates() - 1);	
	_oscMessenger->sendMessage(_world->alive());
	_oscMessenger->collectMessages();
}

void decayApp::draw()
{
	int x, y, z;
	
	if (_ogl->currentPattern() == 6) {
	
		glEnable( GL_LIGHTING );
		glEnable( GL_LIGHT0 );
		
		GLfloat lightPos[] = { 50.0, 50.0, 75.0f, 0.1f };
		
		glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	
	}
	else
	{
		glDisable( GL_LIGHT0 );
		glDisable( GL_LIGHTING );
	}
	
	glPushMatrix();
	gl::multModelView( mRotation );
	if (_world->alive() > 0) {
		_world->resetAlive();
		for (x = 0; x < _world->sizeX(); x++) {
			for(y = 0; y < _world->sizeY(); y++) {
				for(z = 0; z < _world->sizeZ(); z++) {
					_rule->next(&_world->cells[x][y][z], _world->index());
					if (_rule->cellAlive(&_world->cells[x][y][z], _world->index())) {
						_world->incrementAlive();
					}
					_ogl->drawFragment(&_world->cells[x][y][z]);
				}
			}
		}
	}
	glPopMatrix();
	_world->nextIndex();
		
}

void decayApp::getBirthsFromArg(const string &s) {
	stringstream ss(s);
	string item;
	int bsize, i;
	bsize = 0;
	while(std::getline(ss, item, DELIM)) {
		bsize++;
	}
	_births = new int[bsize];
	for (i = 0; i < bsize; i++) {
		std::getline(ss, item, DELIM);
		_births[i] = atoi(item.c_str());
	}
}

void decayApp::getSurvivalsFromArg(const string &s) {
	stringstream ss(s);
	string item;
	int bsize, i;
	bsize = 0;
	while(std::getline(ss, item, DELIM)) {
		bsize++;
	}
	_survivals = new int[bsize];
	for (i = 0; i < bsize; i++) {
		std::getline(ss, item, DELIM);
		_survivals[i] = atoi(item.c_str());
	}	
}


CINDER_APP_BASIC( decayApp, RendererGl )
