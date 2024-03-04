#include <avr/io.h>
#include <util/delay.h>

/* Values of A B C D E F G for pins from PA1 to PA7 */
unsigned char digits[10] = {
	0b0111111, // 0
	0b0000110, // 1
	0b1011011, // 2
	0b1001111, // 3
	0b1100110, // 4
	0b1101101, // 5
	0b1111101, // 6
	0b0000111, // 7
	0b1111111, // 8
	0b1100111  // 9
};

// Function to initialize switch 1
void SW1_Init(void) {
	DDRD &= ~(1 << 2); // Set pin PD2 as input
}

// Function to initialize switch 2
void SW2_Init(void) {
	DDRD &= ~(1 << 3); // Set pin PD3 as input
}

// Function to initialize switch 3
void SW3_init(void) {
	DDRD &= ~(1 << 4); // Set pin PD4 as input
}

// Function to initialize multiplexed 7-segment display
void Multiplixed_7Seg_Init(void) {
	// Set pins PA1 to PA7 and PC6, PC7 as output
	DDRA |= (1 << 1) | (1 << 2) | (1 << 3) | (1 << 4) | (1 << 4) | (1 << 5) | (1 << 6) | (1 << 7);
	DDRC |= (1 << 6) | (1 << 7);
}

// Function to enable only the first 7-segment display
void Enable_first_only(void) {
	PORTC = (1 << 6); // Set pin PC6 high
}

// Function to enable only the second 7-segment display
void Enable_second_only(void) {
	PORTC = (1 << 7); // Set pin PC7 high
}

int main(void) {
	signed char first_seg_value = 0, second_seg_value = 0;
	Multiplixed_7Seg_Init(); // Initialize 7-segment display
	SW1_Init(); // Initialize switch 1
	SW2_Init(); // Initialize switch 2
	SW3_init(); // Initialize switch 3

	while (1) {
		Enable_first_only(); // Enable first 7-segment display
		PORTA = (PORTA & 0) | (digits[first_seg_value] << 1); // Display first segment value
		_delay_ms(5);

		Enable_second_only(); // Enable second 7-segment display
		PORTA = (PORTA & 0) | (digits[second_seg_value] << 1); // Display second segment value
		_delay_ms(5);

		// Check if switch 1 is pressed
		if (!(PIND & (1 << 2))) {
			_delay_ms(30);
			if (!(PIND & (1 << 2))) {
				first_seg_value++; // Increment first segment value
				if (first_seg_value == 10) {
					first_seg_value = 0;
					second_seg_value++;
					if (second_seg_value == 10) {
						second_seg_value = 0;
					}
				}
			}
			while (!(PIND & (1 << 2))); // Wait for switch 1 release
		}
		// Check if switch 2 is pressed
		else if (!(PIND & (1 << 3))) {
			_delay_ms(30);
			if (!(PIND & (1 << 3))) {
				first_seg_value--; // Decrement first segment value
				if (first_seg_value == -1 && second_seg_value == 0) {
					first_seg_value = 0;
					} else if (second_seg_value > 0 && first_seg_value == -1) {
					first_seg_value = 9;
					second_seg_value--;
					} else if (second_seg_value == -1) {
					second_seg_value = 0;
				}
			}
			while (!(PIND & (1 << 3))); // Wait for switch 2 release
		}
		// Check if switch 3 is pressed
		else if (!(PIND & (1 << 4))) {
			_delay_ms(30);
			if (!(PIND & (1 << 4))) {
				first_seg_value = 0;
				second_seg_value = 0;
			}
			while (!(PIND & (1 << 4))); // Wait for switch 3 release
		}
	}
}
