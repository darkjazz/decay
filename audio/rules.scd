~rules = (
	\b3s69n16: (b:[3], s:[6,9], n:16),
	\b34s567n8: (b:[3,4], s:[5,6,7],n:8),
	\b34s345n16: (b:[3,4], s:[3,4,5],n:16),
	\
)

~grph = NetAddr("127.0.0.1", 7000);

~compileRuleMsg = {|rule|
	~rules[rule].asKeyValuePairs.flat
}

~compileRuleMsg.(\b34s567n8)

~grph.sendMsg("/decay/rule/births", 3,4,6,7);

~grph.sendMsg("/decay/rule/survivals",2,5,6,7);

~grph.sendMsg("/decay/rule/states", 12);

~grph.sendMsg("/decay/world/rand", 4, 4, 4, 19, 19, 19, 0.7, 1)

~grph.sendMsg("/decay/world/wirecube", 4, 4, 4, 19, 19, 19)

~grph.sendMsg("/decay/graphics/pattern", 6)

~grph.sendMsg("/decay/quit")

~resp = OSCresponderNode(nil, "/decay/world/alive", {|ti, re, ms|
	ms.postln
}).add

30**3