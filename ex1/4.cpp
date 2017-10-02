#include <iostream>
#include <cmath>
#include <mgl2/mgl.h>

class Point{
    public:
        Point(double x, double y);
        double length();
        void plot();
        void fractal();
        void fractalizeSegment();

        double x;
        double y;
        Point *next;
};

Point::Point(double x, double y){
    this->x = x;
    this->y = y;
    next = NULL;
}

double Point::length(){
    double delta_x;
    double delta_y;
    double curr_x = x;
    double curr_y = y;
    double length = 0;

    Point *curr = this;

    while(curr->next != NULL){
        curr = curr ->next;

        delta_x = fabs(curr_x - curr->x);
        delta_y = fabs(curr_y - curr->y);
        length += sqrt(pow(delta_x, 2) + pow(delta_y, 2));

        curr_x = curr->x;
        curr_y = curr->y;
    }

    return length;
}

void Point::plot(){
    mglGraph gr;
    std::vector<double> x_values;
    std::vector<double> y_values;

    Point *curr = this;
    x_values.push_back(curr->x);
    y_values.push_back(curr->y);

    
    // load all values from all points
    while(curr->next!= NULL){
        curr = curr -> next;
        x_values.push_back(curr->x);
        y_values.push_back(curr->y);
    }

    // pack all data into a Graph-readable format
    int size = x_values.size();
    mglData x_data(size), y_data(size);

    for(int n=0; n < size; n++){
        x_data.a[n] = x_values.at(n);
        y_data.a[n] = y_values.at(n);
    }

    // plot the data points
    gr.Plot(x_data, y_data);

    // Save to file
    gr.WriteFrame("Sirpinski.png");
}

void Point::fractalizeSegment(){
    //check if there is next point
    if(next == NULL) {
        return;
    }
    // starting points of the segment
    double x0 = x;
    double y0 = y;

    // get the endpoints of the line-segments
    double x4 = next->x;
    double y4 = next->y;

    // Get direction between two new points
    double delta_x = x4 - x0;
    double delta_y = y4 - y0;

    // divide line between point1 and point2 in 3 parts
    // with points numbered from 0 to 3 - 
    // where 0 and 4 are already given by end and starting point
    
    // a1 : one third in between p1 and p2
    double x1 = x0 + delta_x/3;
    double y1 = y0 + delta_y/3;
    Point *a1 = new Point(x1, y1);

    // a3 : two thirds in between p1 and p2
    double x3 = x0 + (2.0/3.0)* delta_x;
    double y3 = y0 + (2.0/3.0)* delta_y;
    Point *a3 = new Point(x3, y3);

    // a2: The top of the triangle
    double x2 = x0 + delta_x/2 - (sqrt(3)/6)*delta_y;
    double y2 = y0 + delta_y/2 + (sqrt(3)/6)*delta_x;
    Point *a2 = new Point(x2, y2);

    // Link all the points together
    a3->next = next;
    a2->next = a3;
    a1->next = a2; 
    next     = a1;
}

void Point::fractal(){
    Point *next;
    Point *curr = this;

    while(curr->next !=NULL){
        next = curr->next;
        curr->fractalizeSegment();
        curr = next;
    }
}

int main(){
    Point *a1 = new Point(-1, -0.5);
    Point *a2 = new  Point(1, -0.5);
    a1->next = a2;

    for(int n=0; n<10;n++){
        std::cout << a1->length() << std::endl;
        a1->fractal();
    }

    a1->plot();
    return 0;
}
