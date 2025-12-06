#include "libspider.h"
#include "SPColor.h"
#include <stdio.h>
#include <string>
using namespace std;
/*!
 * From http://www.dreamincode.net/forums/topic/58058-converting-rgb-to-hex/
 **/
string RGBToHex(int rNum, int gNum, int bNum) {
	string result;
    result.append("#");
	char r[255];
	snprintf(r, 255, "%.2X", rNum);
	result.append(r );

	char g[255];
	snprintf(g, 255, "%.2X", gNum);
	result.append(g );

	char b[255];
	snprintf(b, 255, "%.2X", bNum);
	result.append(b );

	return result;
}



namespace spider {
/**
Colors
**/
short SPColor::getR() {
	return this->r;
}
short SPColor::getG(){
	return this->g;
}
short SPColor::getB(){
	return this->b;
}
short SPColor::getA() {
	return this->a;
}
string SPColor::toHTMLColor() {
    return RGBToHex(this->r, this->g, this->b);
}
void SPColor::setR(short r) {
	this->r = r;
}
void  SPColor::setG(short g) {
	this->g = g;
}
void  SPColor::setB(short b){
	this->b = b;
}
void  SPColor::setA(short a){
	this->a = a;
}
SPColor::SPColor(short r, short g, short b, short a){
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}

SPColor::SPColor() {
	this->r = 0;
	this->g = 0;
	this->b = 0;
	this->a = 0;
}

SPColor::SPColor(const string& html) {
	// TODO Fix this later
	int color = htmlToColor(html);

	short r, g, b, a = 0;
	if(html.length() > 6 + 1) {
		r = color >> (16 + 8) & 0xff;
		g = color >> 16 & 0xff;
		b = color >> 8 & 0xff;
	} else {
		r = color >> 16 & 0xff;
		g = color >> 8 & 0xff;
		b = color >> 0 & 0xff;
	}
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}
};
