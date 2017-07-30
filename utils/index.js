var keyWidth = [
	[1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
	[1.25, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1.75],
	[1.75, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1.25, 1],
	[1.25, 1.25, 1.25, 1.75, 2.75, 1.25, 1.25, 1.25, 1]
]

console.log(keyWidth);
const W = 19;

for (var y=0; y<4; ++y) {
	var rowKeys = keyWidth[y];
	var rowWidth = 0;
	for (var x=0; x<rowKeys.length; ++x)
	{
		rowWidth += rowKeys[x]/2.0 * W;
		process.stdout.write((rowWidth).toString() + " ");
		rowWidth += rowKeys[x]/2.0 * W;
	}
	console.log(rowWidth);
}