
// default includes
#include <iostream>
#include <vector>
#include <string>

// an class shared by all the 5 parts of the system
class satellite_component {
protected:

	// here is stored the local_system_state
  signed long long int local_system_state = 0;

	// actually setting the state
  void set_local_system_state(signed long long int system_state_input)
  {
    local_system_state = system_state_input;
  }

public:

	// set the state of the system for this particular object, each particular object
  void call_set_local_system_state(signed long long int state_int)
  {
    set_local_system_state(state_int);
  }
};

class satellite_printer : public satellite_component {
protected:
	std::string local_user_input = "void";

	// display_prompt just prints a prompt for the program depending on the local_system_state
	void display_prompt()
	{
		if(local_system_state == 0)
		{
			std::cout << " [satellite]";
		}

		if(local_system_state == 50)
		{
			std::cout << " [satellite-console]";
		}

		if(local_system_state == 100)
		{
			std::cout << " [satellite-compiler]";
		}

		if(local_system_state == 200)
		{
			std::cout << " [satellite-interpreter]";
		}

		if(local_system_state == 300)
		{
			std::cout << " [satellite-vm]";
		}
	}

	// prints a message in display_str and a prompt, and a newline
	void display_message(std::string display_str, bool prompt_bool, bool newline_bool)
	{
		if(prompt_bool == true)
		{
			display_prompt();
		}

		std::cout << display_str;

		if(newline_bool == true)
		{
			std::cout << "\n";
		}
	}

	// some dividers to display
	void display_divider(signed long long int divider_input)
	{
		if(divider_input == 0)
		{
			std::cout << "================================================================================\n";
		}

		if(divider_input == 1)
		{
			std::cout << " --+ --+ --+ --+ --+ --+ --+ --+ --+ --+ --+ --+ --+ --+ --+ --+ --+ --+ --+ --+\n";
		}

		if(divider_input == 2)
		{
			std::cout << "==+ ==+ ==+ ==+ ==+ ==+ ==+ ==+ ==+ ==+ ==+ ==+ ==+ ==+ ==+ ==+ ==+ ==+ ==+ ==+ \n";
		}

		if(divider_input == 3)
		{
			std::cout << "}}}}}-----                                                            -----{{{{{\n";
		}

		if(divider_input == 4)
		{
			std::cout << "          ))))))))))----------                    ----------((((((((((          \n";
		}

		if(divider_input == 5)
		{
			std::cout << "::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n";
		}
	}

	// collect_input just a getline(std::cin) statement, doesn't return input
	void collect_input()
	{
		std::getline(std::cin, local_user_input);
	}

	// return_input() that was collected by collect_input
	std::string return_input()
	{
		return(local_user_input);
	}
	
public:

	// display a prompt
	void call_display_prompt()
	{
		display_prompt();
	}

	// to replace the print function, it includes a bool to display the prompt, and a bool to print a newline
	// which are automatically activated by default with these true values below
	void call_display_message(std::string message_str, bool prompt_bit = true, bool newline_bit = true)
	{
		display_message(message_str, prompt_bit, newline_bit);
	}

	// displays a divider
	void call_display_divider(signed long long int divider_input)
	{
		display_divider(divider_input);
	}

	// collect_input,
	void call_collect_input()
	{
		collect_input();
	}

	// return input collected by collect_input();
	void call_return_input()
 	{
		return(return_input());
	}

};

// the console class
class satellite_console : public satellite_component {
protected:

public:

};

// the compiler class
class satellite_compiler : public satellite_component {
protected:

public:

};

// the interpreter class
class satellite_interpreter : public satellite_component {
protected:

public:

};

// the virtual machine class
class satellite_vm : public satellite_component {
protected:

public:

};

// the main satellite_system class
class satellite_system : public satellite_component {
protected:

	// a variable that controls when the program shuts down
	bool shutdown_bool = false;

	// the physical object that we use for each type of system component
  satellite_printer the_printer;
  satellite_console the_console;
  satellite_compiler the_compiler;
  satellite_interpreter the_interpreter;
  satellite_vm the_vm;

public:

	// the link to the physical object
  satellite_printer *orbital_printer = &the_printer;
  satellite_console *orbital_console = &the_console;
  satellite_compiler *orbital_compiler = &the_compiler;
  satellite_interpreter *orbital_interpreter = &the_interpreter
  satellite_vm *orbital_vm = &the_vm;

  void set_global_system_state(signed long long int system_state_int)
	{
		// set the various states for each object
		orbital_printer->call_set_local_system_state(system_state_int);
		orbital_console->call_set_local_system_state(system_state_int);
		orbital_compiler->call_set_local_system_state(system_state_int);
		orbital_interpreter->call_set_local_system_state(system_state_int);
		orbital_vm->call_set_local_system_state(system_state_int);

		// call satellite_system object's call_set_local_system_state()
		call_set_local_system_state(system_state_int);

		// debug_mode is displaying a message
		if(debug_mode == true)
		{
			orbital_printer->call_display_message(("debug: system_state set to: " + std::to_string(system_state_int)));
		}
	}

	// call for a shutdown just sets a variable to be returned by return_shutdown()
	void call_shutdown()
	{
		shutdown_bool = true;
	}

	// return_shutdown returns the state of the shutdown bool variable
	void return_shutdown()
	{
		return(shutdown_bool);
	}
};

int main(int argc, char *argv[])
{
  std::cout << "Satellite Bytecode System v.002.13\n";

	// begin the default satellite_system class object satellite
  satellite_system satellite;

	// production collects and parses input, and shutdown_bit is to shutdown
  bool production = true;
	bool shutdown_bit = false;

	// the actual while loop that everything stems from
	// collecting input, and returning input in the next function.
  while (production == true)
  {
			// call satellite.orbital_printer and the function is display_prompt();
      satellite.orbital_printer->call_display_prompt();
		
			// call satellite object's orbital_printer's call_collect_input()
      satellite.orbital_printer->call_collect_input();

			// console_parser parses console input, together with the main satellite object
			// the satellite object is required as it holds not only the actual console input,
			// but also various functions that are called..
      satellite = console_parser(satellite);

			// check if there was a call to shutdown
			shutdown_bit = satellite.return_shutdown();

			// if there was a call to shutdown, stop the program,
			if(shutdown_bit == true)
			{
				production = false;
			}
  }

	// a shutdown must have been called!
  return(0);
}

// the console parsing function (parses console input: like: help("about");)
satellite_system console_parser(satellite_system satellite)
{
	// display that we've arrived at this function
	satellite.orbital_printer->call_display_message("console_parser();");

	// declare a string to hold the input we will later parse,
	std::string local_user_input = "void";

	// return the input collected in the main while loop
	local_user_input = satellite.orbital_printer->call_return_input();

	// this is part of my "insta-quit", it quits the program almost instantly, if quit is detected
	// by the various if statements.
	if(local_user_input == "quit" || local_user_input == "quit()" || local_user_input == "quit();")
	{
		shutdown_state = true;
	}

	// another quit if statement
	if(local_user_input == "QUIT" || local_user_input == "QUIT()" || local_user_input == "QUIT();")
	{
		shutdown_state = true;
	}

	// an exit statement, same function as the quit statement...
	if(local_user_input == "exit" || local_user_input == "exit()" || local_user_input == "exit();")
	{
		shutdown_state = true;
	}

	// another quit statement for capital letters...
	if(local_user_input == "EXIT" || local_user_input == "EXIT()" || local_user_input == "EXIT();")
	{
		shutdown_state = true;
	}

	// call a shutdown to be picked up when we return to the int main's main while loop
	if(shutdown_state == true)
	{
		satellite.call_shutdown();
	}

	// return to the main while loop
	return(satellite);
