function Generate(Dec) {
	if (Dec == -1) {
		Dec = document.getElementById("BinNbr").value;
		if (isNaN(Dec)) {
			Dec = 0;
		}
		Dec = dec2bin(BigInt(Dec));
	}
	Bin = "0".repeat(64 - Dec.length) + Dec;
	
	var Class;
	for (i = 1; i <= 64; i++) {
		Class = "EmptyBlock";
		if (Bin[64-i] == "1") {
			Class = "FullBlock";
		}
		ObjectBasedInt(i).className = Class;
	}
}

function ObjectBasedInt(Value) {
	return document.querySelector(".Grid").childNodes[1 + (8-Math.ceil(Value/8))*2].childNodes[15-((Value-1)%8)*2];
}

function RandomValue() {
	// Generate random 64 bits integer
	var Nbr = Math.floor(Math.random() * Math.pow(2, 32)).toString(2) + Math.floor(Math.random() * Math.pow(2, 32)).toString(2);
	Generate(Nbr);
}


var All = [460551, 771, 1, 4311810305, 16843009, 65793, 257, 31, 15, 7, 3, 259, 515, 770, 769, 459009, 65799, 263175, 459780, 66305, 519, 131842, 1794, 65795, 1031, 197122, 1793, 131587, 1796, 196865, 263, 197379, 1799, 66306, 1539, 131841, 774, 66052, 262657, 258, 513]

function RandomShape() {
	Generate(dec2bin(All[Math.floor(Math.random() * 41)]));
}

function dec2bin(dec) {
	return parseInt(dec).toString(2);
}
