#include "shape.hpp"


//Aditya Vikram Gupta
//BD-2  avgupta3

//Intro Paragraph:
//In this program we write functions to read certain parameters of different shapes and then calculate their area and volumes
//To achieve this we make use of constructors and functions in which we assign the name of the shape, width, height, radius etc.
//The different shapes we test are Rectangle, Circle, Sphere and a Rectangular prism
//For each of these the constructor assigns the value of their dimensions
//The function of the type <ShapeName>::getArea()const calculates the Area
//The function of thr type <ShapeName>::getVolume()const calculates the Volume
//The function CreateShapes reads the .txt file and then initializes the objects


//Base class
//Please implement Shape's member functions
//constructor, getName()

//constructor

Shape::Shape(string name){
  name_ = name;
}

//return name as a string
string Shape::getName(){
  return name_;
}

//Base class' constructor should be called in derived classes'
//constructor to initizlize Shape's private variable



//Rectangle
//Please implement the member functions of Rectangle:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here

//constructor
Rectangle::Rectangle(double width, double length):Shape("Rectangle"){
  width_ = width;
  length_ = length;
}

//this function returns the area of the Rectangle
double Rectangle::getArea()const{
  return width_ * length_;
}

//this function returns the volume of a rectangle which is just going to be 0
double Rectangle::getVolume()const{
  return 0;
}

//this is overloading the operator "+"
//this is created to add two rectangles
Rectangle Rectangle::operator + (const Rectangle& rec){
  Rectangle a;
  a.width_ = rec.width_ + this->width_ ;
  a.length_ = rec.length_ + this->length_ ;
  return a;
}

//this is created to overload the operator "-"
//this lets us subtract two triangles
//to achive this we select the max(0, difference between teo dimensions provided)
Rectangle Rectangle:: operator - (const Rectangle& rec){
  Rectangle a;
  if((this->width_ - rec.width_) > 0){
    a.width_ = this->width_ - rec.width_;
  }
  else a.width_ = 0;

  if((this->length_ - rec.length_) > 0){
    a.length_ = this->length_ - rec.length_;
  }
  else a.length_ = 0;
  return a;
}

double Rectangle::getWidth()const{return width_;}
double Rectangle::getLength()const{return length_;}


//Circle
//Please implement the member functions of Circle:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here

//constructor for the shape Circle
Circle::Circle(double radius):Shape("Circle"){
  radius_ = radius;
}

// calculate the area of the circle
double Circle::getArea()const{
  return radius_*radius_ * M_PI;
}
//calculate the volume of the circle =  0
double Circle::getVolume()const{
  return 0;
}

//overloading operator "+"
//this lets us add two circles
// variable "c" of the type Circle needs to be initialized to 0 since it wasn't in the header file
Circle Circle:: operator + (const Circle& cir)
{
  Circle c(0);
  c.radius_ = cir.radius_ + this->radius_ ;
  return c;
}

//overloading operator "-"
//initialize "c" just like in the previous function
//select the max(0, the differece of the two radii)
Circle Circle::operator - (const Circle& cir){
  Circle c(0);
  if((this->radius_ - cir.radius_) > 0){
    c.radius_ = this->radius_ - cir.radius_;
  }
  else c.radius_ = 0;

  return c;
}

double Circle::getRadius()const{return radius_;}

//Sphere
//Please implement the member functions of Sphere:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here

//Constructor for Sphere
Sphere::Sphere(double radius):Shape("Sphere"){
  radius_ = radius;
}

//calculate the area of the Sphere
double Sphere::getArea()const{
  return 4 * pow(radius_, 2.0) * M_PI;
}

//Calculate the volume of the Sphere
double Sphere::getVolume()const{
  return (4.0/3.0) * pow(radius_, 3.0) * M_PI;
}

//Overload "+" for Sphere
//lets us add two sheres
//initialize Spaere s to 0
Sphere Sphere:: operator + (const Sphere& sph)
{
  Sphere s(0);
  s.radius_ = sph.radius_ + this->radius_ ;
  return s;
}

//overloading operator "-"
//Initialize Sphere s to 0
//select max(0, the difference of two radii)
Sphere Sphere::operator - (const Sphere& sph){
  Sphere s(0);
  if((this->radius_ - sph.radius_) > 0){
    s.radius_ = this->radius_ - sph.radius_;
  }
  else s.radius_ = 0;
  return s;
}

double Sphere::getRadius()const{return radius_;}

//Rectprism
//Please implement the member functions of RectPrism:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here

//Constructor for Rectangular prism
RectPrism::RectPrism(double width, double length, double height):Shape("RectPrism"){
  width_ = width;
  length_ = length;
  height_ = height;
}

//Calculate the area for RectPrism
double RectPrism::getArea()const{
  return 2 * ((length_ *  width_)  + (length_ * height_) + (width_ * height_));
}

double RectPrism::getVolume()const{
  return length_ * width_ * height_;
}

//Overload the operator "+"
//lets us add RectPrisms
//initialized Rect rp to 0
RectPrism RectPrism:: operator + (const RectPrism& rectp)
{
  RectPrism rp(0,0,0);
  rp.width_ = rectp.width_ + this->width_ ;
  rp.length_ = rectp.length_ + this->length_ ;
  rp.height_ = rectp.height_ + this->height_ ;

  return rp;
}

//Overload the operator "-"
//select max(width/length/height , 0)
RectPrism RectPrism::operator - (const RectPrism& rectp){
  RectPrism rp(0,0,0);
  if(this->width_ > rectp.width_){
    rp.width_ = this->width_ - rectp.width_;
  }
  else{
    rp.width_ = 0;
  }
  if((this->length_ - rectp.length_) > 0){
    rp.length_ = this->length_ - rectp.length_;
  }
  else{
    rp.length_ = 0;
  }
  if((this->height_ - rectp.height_) > 0){
    rp.height_ = this->height_ - rectp.height_;
  }
  else{
    rp.height_ = 0;
  }
  return rp;
}

double RectPrism::getWidth()const{return width_;}
double RectPrism::getHeight()const{return height_;}
double RectPrism::getLength()const{return length_;}



// Read shapes from test.txt and initialize the objects
// Return a vector of pointers that points to the objects
vector<Shape*> CreateShapes(char* file_name){
	//@@Insert your code here
  int r;
        ifstream ifs(file_name, std::ifstream::in);
        ifs >> r;
        vector<Shape*> shapes;
        int i;
        double dim1;
        double dim2;
        double dim3;
        string name;

        for (i=0; i<r; i++)
        {
                ifs >> name;
                if (name == "Rectangle") {
                        ifs >> dim1 >> dim2;
                        Rectangle* rect = new Rectangle(dim1, dim2);
                        shapes.push_back(rect);
                } else if (name == "Circle") {
                        ifs >> dim1;
                        Circle* cir = new Circle(dim1);
                        shapes.push_back(cir);
                } else if (name == "Sphere") {
                        ifs >> dim1;
                        Sphere* sph = new Sphere(dim1);
                        shapes.push_back(sph);
                } else  {
                        ifs >> dim1 >> dim2 >> dim3;
                        RectPrism* rectp = new RectPrism(dim1, dim2, dim3);
                        shapes.push_back(rectp);
                }
        }

	return shapes;
}

// call getArea() of each object
// return the max area
double MaxArea(vector<Shape*> shapes){
	double max_area = 0;
	//@@Insert your code here
  int i;
  for (i= 0; i < shapes.size(); i++ ){
    if (shapes[i]->getArea() > max_area)
			max_area = shapes[i]->getArea();
  }

	return max_area;
}


// call getVolume() of each object
// return the max volume
double MaxVolume(vector<Shape*> shapes){
	double max_volume = 0;
	//@@Insert your code here
  int i;
  for (i= 0; i < shapes.size(); i++ ){
    if (shapes[i]->getVolume() > max_volume)
			max_volume = shapes[i]->getVolume();
  }

	return max_volume;
}
