~buffers = "/Users/alo/sounds/fx_loops/fx*".pathMatch.collect({|path|
	Buffer.read(s, path)
});

Ndef(\buf).play;
Ndef(\dwt).play;

Ndef(\buf, {
	PlayBuf.ar(1, ~buffers[1], loop: 1).dup
})

Ndef(\dwt, {
	var src, chain;
	src = PlayBuf.ar(1, ~buffers[1], 0.125, loop: 1) ** 0.5;
	chain = DWT(LocalBuf(1024), src, wavelettype: 9);
//	chain = WT_TimeWipe(chain, LFSaw.kr(1).range(0, 1));
	chain = WT_Freeze(chain, LFPulse.kr(2, 0, 0.25).range(0, 1), LFSaw.kr(1).range(0, 1));
	IDWT(chain).dup
})

Ndef(\buf).stop
Ndef(\dwt).stop

s.queryAllNodes

MasterEQ(2)

155*115