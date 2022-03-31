#ifndef __FIGURES_HPP__
# define __FIGURES_HPP__

typedef struct	s_point {				//_____________
	int x;						//__[ x , y ]__
	int y;						//____POINT____
}	point;						//_____________

class Circle {						//_____________________________
	point	center;					//_______.-._____CIRCLE________
	int 	r;					//_____-%%%%%-_________________
	char	chr;					//____.%%%%%/%.________________
	bool	filled;					//___-%%%%%/%%%-_______________
	public:						//___.%%%%O%%%%._______________
		void	set(point, int, char);		//____.%%%%%%%.___O:center_____
		bool	belongs_to(point);		//_____-%%%%%-____/:radius(r)__
		int	area(void);			//______.%%%.__________________
		char	get_chr(void);			//_______-.-___________________
};							//_____________________________

class Rectangle {					//_____________________________
	point	tlc;					//__RECTANGLE__________________
	int 	h;					//_______________w_____________
	int	w;					//_______<------------->_______
	char	chr;					//_____________________________
	bool	filled;					//_______Γ-------------ꓶ__∧____
	public:						//______ꓶ|%%%%%%%%%%%%%|__|____
		void	set(point, int, int, char);	//_____/_|%%%%%%%%%%%%%|__|h___
		bool	belongs_to(point);		//____/__|%%%%%%%%%%%%%|__|____
		char	get_chr(void);			//___/___|%%%%%%%%%%%%%|__|____
		int	area(void);			//_rtc___L-------------⅃__v____
};							//_____________________________

class	Triangle {					//_____________________________
	point 	a;					//___________TRIANGLE__________
	point 	b;					//_______b_____________________
	point 	c;					//______/%\____________________
	char	chr;					//_____/%%%\___________________
	bool filled;					//____/%%%%%\__________________
	public:						//___a-------c_________________
		void	set(point, point, point, char);	//_____________________________
		bool	belongs_to(point);		//_____________________________
		int	area(void);			//_____________________________
};							//_____________________________

#endif
