Welcome to GSX Studio! - Created by Serious

Announcements:
	-Please consider donating, because projects like these are not free for the creator, and take an extreme amount of effort! Any amount helps me!

Special Thanks to the following people:
	-Extinct ~ Support, lots of help with function definitions and alpha testing.
	-SyGnUs ~ GSC Dumper, massive help in the creation and development of unsafe custom functions
	-Agreedbog ~ Help with some assembly for custom functions
	-Alfredo ~ Support, small toolwork here and there
	-Loz ~ General GSC Support
	-Kokole, Nukem, Master131 ~ Original reversal of Black Ops II GSC
	-DTX12 ~ His original compiler work
	-Jwm614 ~ Help with some PC injection addresses and the text editor
	-XTul, TCM, Inc ~ Alpha testing
	-jakedragon24, Cykotic ~ Helped with Xbox SESR Database Collection

Changelog:
	Version 1.2a	  
		- Private Alpha
	Version 1.4.0.0 
		- Public Alpha
	Version {VERSION} (Public Beta)
		New Features:
			- Full Number support (hex, float, double, etc)
			- #region support for code organization
			- 'waitmin': Supports waiting the absolute smallest time allowed by the game engine without triggering the network freeze logic
			- 'goto' and 'label':
				> Mark a section by typing an identifier followed by ':'
				> type goto followed by the name of the section to jump to that section!
				> Example code:
								start:
									self iprintln("Hi there!");
									waitmin;
									goto start;
			- Detects undefined local variables automatically during compilation
			- Syntax Update: You can now include, define functions, define macros, etc. in any order
			- New advanced script protection!
				> Used for special portions of code that need to be more secure than usual
				> Syntax: $(section_identifier){ /*code here*/ }
				> Example code:
								$(auto_verify)
								{
									foreach(player in level.players)
										if(player IsFounder())
											player CreateMenu(FOUNDER_ACCESS);
								}
			- New Memory Based Functions (calls are highlighted in red)
				- Please note that these functions are run on the HOST ONLY. You cannot call these functions and set memory on a client's machine (yet :D)
					> void SetInt( uint address, uint value )
					> int32 GetInt( uint address )
					> void SetByte( uint address, byte value )
					> byte GetByte( uint address )
					> void SetFloat( uint address, float value )
					> float GetFloat( uint address )
					> void SetString( uint address, string value )
					> void SetBytes( uint address, byte[] value )

			- New RPC Function!
				- Call any function embedded in the game or loaded into process memory!
				- Please note that this function is run on the HOST ONLY.
					> int RPC( address, params... )
						- RPC returns whatever was loaded into eax/r3 from the function called. This means that if the function returns nothing you will get '0' back
						- This also means that return values are almost always pointers (unless simple types)
						- You will need to write any custom structs to memory and pass references through parameters
						- I will release a full RPC tutorial once the beta is out.

			- New Script Environment String Reduction feature:
				> Reduces string usage on platform by on average 33%, saving you nearly 3000 strings for your scripts.

			- New array shorthanding:
				> Use the 'array' keyword before a declaration to set up an array shorthand
					> Example code:
									array MyArray = { "Hello", "World", "!" };



		Bug Fixes:
			- Fixed 'Form has already been shown' exception
			- Fixed string definition so its coloration no longer exceeds its boundaries
			- Fixed an issue where the updater would loop infinitely if anti-virus removed the update file before the process finished
			- Fixed an issue where compiling certain gsc files would result in the linker producing false errors
			- Fixed an issue with steam injection that caused a windows access exception
			- Fixed an issue with PC Zombies injection that caused inadvertent overlapping of memory segments
			- Fixed an exception that occurred when starting GSX Studio without the default styling sheet
		
		Known Bugs:
			> Defining functions with the same name as a builtin will confuse the linker and optimizer, causing script errors.
			> Loading a file with a large horizontal region may cause the scrollbar to be incorrectly limited until the longest line in the script has been edited

Main Features:
	- Faster Compiler
	- Source protection built in
	- Script optimization
	- Many bug fixes from the original compiler
	- Autocomplete
	- Fully contained projects
	- Multi-Script support
	- Syntax error navigation and better accuracy
	- Basic Macros (define identifier expr;)
	- Post build linker that catches unresolved functions

P.S.
	- Please note that this is an beta build. This application has many features disabled which may never be implemented. 
	- This application may also have some bugs, so please report any bugs that you notice to me using About->Report a bug