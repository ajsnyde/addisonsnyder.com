#ifndef SHAPEO_H
#define SHAPEO_H
class shapeO {
public:

	shapeO() {};
    virtual ~shapeO() {};
    bool collidesWith( shapeO *);
    void getRect(double & X, double & Y, double & W, double & H)
	{  X = x; Y = y; W = width; H = height; }
    void setRect(double X , double Y, double W, double H) 
	{ x = X; y = Y; width=W; height=H;}
protected:
    double x,y, height, width;
};
#endif
