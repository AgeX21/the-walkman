#include <nds.h>

u16 timer_used; //bitmap representation of the timer
void*** timer_func[4]; // 2D array of void*
u16* timer_alloc[4]; // how many void* allocated for each timer
u16* timer_length[4]; // how many void* in each timer

int milliseconds, seconds, minutes, hours;

/*
	
*/
void timer_init();
void timer_walk_animations();

// Timer set at 100ms for multiples uses
void timer_100ms_isr();

void timer_menu_animations();

/*
	loop through timer_func[i]
	call the function
	return
*/
void timer0_isr();
void timer1_isr();
void timer2_isr();
void timer3_isr();

/*
	@brief 	simplified function to start a timer with a function

	@return	0-3 : started timer 0-3, 4 : no timer available 

	initialize the timer with its default function
	call add_timer with the corresponding timer number and the void*
	return timer number
*/
u16 start_timer(u16 hz, void* func);

/*
	@brief	add a void* to the list of func to call

	@return	position of the function in the timer list

	check allocated size (len == alloc)
	realloc if necessary
	append to the list
	return the correct index
*/
u16 add_timer(u16 timer_number, void* func);

/*
	@brief	remove a void* from the list of func to call

	check allocated size
	remove from the list
*/
void remove_timer(u16 timer_number, u16 index);

/*
	stop the corresponding timer;
*/
void stop_timer(u16 timer_number);
