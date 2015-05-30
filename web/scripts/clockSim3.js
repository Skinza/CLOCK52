/* global data */
var totalPixels = 125; // 1 based
var gridOffset = 2; // 0 based
var gridCols = 11;
var gridRows = 11;

var animationSpeed = 3;
var animationFrame = 0;
var currentAnimation;

function bootstrap() {
	console.log("go gadget go!");
	/*for(var run=0; run <= 4; run++) {
		for(var i=0; i < totalPixels; i++) {
			if(run==0) { setPixel(i,255,0,0); }
			if(run==1) { setPixel(i,0,255,0); }
			if(run==2) { setPixel(i,0,0,255); }
			if(run==3) { setPixel(i,255,255,255); }
			//if(run==4) { setPixel(i,0,0,0); }
		}
	}*/

	animatePost();	
	//startClock();
}

function animatePost() {
	currentAnimation = requestAnimationFrame(animatePost);
	drawPostFrame(animationFrame++);
}

function drawPostFrame(frame) {
	//console.log("post frame " + frame);
	if(frame < (totalPixels*5)) { 
		if(frame < totalPixels) { setPixel(frame,255,0,0); }
		if((frame >= totalPixels) && (frame < (totalPixels*2))) { setPixel(frame-(totalPixels),0,255,0); }
		if((frame >= totalPixels*2) && (frame < (totalPixels*3))) { setPixel(frame-(totalPixels*2),0,0,255); }
		if((frame >= totalPixels*3) && (frame < (totalPixels*4))) { setPixel(frame-(totalPixels*3),255,255,255); }
		if((frame >= totalPixels*4) && (frame < (totalPixels*5))) { setPixel(frame-(totalPixels*4),10,10,10); }
	} else { cancelAnimationFrame(currentAnimation); console.log("post done;"); startClock(); }
}

function startClock() {
	//create green cross
	setGridPixel(0,0,0,255,0); // x,y,red,green,blue
	setGridPixel(1,1,0,255,0); // x,y,red,green,blue
	setGridPixel(2,2,0,255,0); // x,y,red,green,blue
	setGridPixel(3,3,0,255,0); // x,y,red,green,blue
	setGridPixel(4,4,0,255,0); // x,y,red,green,blue
	setGridPixel(5,5,0,255,0); // x,y,red,green,blue
	setGridPixel(6,6,0,255,0); // x,y,red,green,blue
	setGridPixel(7,7,0,255,0); // x,y,red,green,blue
	setGridPixel(8,8,0,255,0); // x,y,red,green,blue
	setGridPixel(9,9,0,255,0); // x,y,red,green,blue
	setGridPixel(10,10,0,255,0); // x,y,red,green,blue
	setGridPixel(10,0,0,255,0); // x,y,red,green,blue
	setGridPixel(9,1,0,255,0); // x,y,red,green,blue
	setGridPixel(8,2,0,255,0); // x,y,red,green,blue
	setGridPixel(7,3,0,255,0); // x,y,red,green,blue
	setGridPixel(6,4,0,255,0); // x,y,red,green,blue
	setGridPixel(5,5,0,255,0); // x,y,red,green,blue
	setGridPixel(4,6,0,255,0); // x,y,red,green,blue
	setGridPixel(3,7,0,255,0); // x,y,red,green,blue
	setGridPixel(2,8,0,255,0); // x,y,red,green,blue
	setGridPixel(1,9,0,255,0); // x,y,red,green,blue
	setGridPixel(0,10,0,255,0); // x,y,red,green,blue
}

// set grid pixel zero based, 0,0 = linksboven
function setGridPixel(x,y,red,green,blue) {
	if(y%2 == 0) { // het is een forward regel
		setPixel(((y*gridCols) + x) + gridOffset,red,green,blue);
	} else { // pixels lopen reverse door bedrading
		setPixel(((y*gridCols) + ((gridCols-1)-x)) + gridOffset,red,green,blue);
	}
}

function setPixel(pos,red,green,blue) {
	document.getElementById("LED-"+pos).style.color = "rgb("+red+","+green+","+blue+")";
}
