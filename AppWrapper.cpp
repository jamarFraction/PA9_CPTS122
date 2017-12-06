#include "AppWrapper.h"

AppWrapper::AppWrapper()
{
	//construct greatness
}

void AppWrapper::StartApplication() {

	//init for rand
	srand((unsigned int)time(NULL));

	//call the menu function
	this->DisplayMenu();

}

void AppWrapper::DisplayMenu() {

	//Menu controller
	int option = 0;

	//lLoop that controls the exit of the app
	do {

		//Loop that takes care of input validation
		do {

			//clear the console
			system("cls");

			//print the menu for visualizations
			cout << "\"Insert Better Menu Title\"\n\n1. Squares Playground\n2. Circles Playground\n3. Exit" << endl;

			cin >> option;

		} while (option < 1 || option > 3);	//exit condition will change with new menu items 



		//Switch statement for each item number in the menu
		switch (option) {

		case 1:

			//Start the playground
			this->SquaresPlayground();
			break;

		case 2:

			//Start the playgrund
			this->CirclesPlayground();
			break;

		case 3:

			//Display exit message? exit condition will be triggered to exit this function
			//and end the application
			cout << "Later, fam" << endl;
			break;

		}

	} while (option != 3);
	



}

void AppWrapper::SquaresPlayground() {

	//Declare a RenderWindow object
	sf::RenderWindow window;

	//returns VideoMode for current display resolution of the device being used
	sf::VideoMode deviceScreenResolution = sf::VideoMode::getDesktopMode();

	//create the window
	this->CreateNewWindow(window, deviceScreenResolution, "Sqaures Playground");

	
	//pass to a drawing algo?
	//pattern for drawing (to look like movement) is clear, draw, display
	this->DoubleDropColor(window);
	//this->DropColor(window);

}

void AppWrapper::CreateNewWindow(sf::RenderWindow &window, sf::VideoMode &screenResolution, string windowTitle) {

	if (screenResolution.isValid()) {

		//Create a window at full resolution capability/size	
		window.create(screenResolution, windowTitle);

	}
	else {

		//invalid window size, create a window with a hard-coded size
		window.create(sf::VideoMode(600, 600), windowTitle);

	}

}

void AppWrapper::DropColor(sf::RenderWindow &window) {


	//create the array of 50 squares with already randomized values 
	DropcolorSquare squares[50];

	//variable to track X position of printing
	int printPos = 0;

	
	for (int i = 0; i < 50; i++) {

		//start at (0,0), move right 1 side length each loop
		squares[i].SetPosition(printPos, 0);

		int dropLength = squares[i].GetDropLength();

		//vertical drop loop
		for (int j = 0; j < dropLength; j += 2) {

			squares[i].SetPosition(printPos, j);

			window.draw(squares[i]);

			window.display();

		}

		printPos += squares[i].GetSideLength();

	}

	
	//necessary to keep the window open and not crash the program during/after execution
	while (window.isOpen()){
		//polling of events.. may find use elsewhere
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
	}
}

void AppWrapper::DoubleDropColor(sf::RenderWindow &window) {


	//create two arrays of 50 squares with already randomized values 
	DropcolorSquare squares1[50];
	DropcolorSquare squares2[50];


	//variable to track X position of printing
	int printPos = 0;

	//Top half of the visual
	for (int i = 0; i < 50; i++) {

		//start at (0,0), move right 1 side length each loop
		squares1[i].SetPosition(printPos, 0);

		int dropLength = squares1[i].GetDropLength();

		//vertical drop loop
		for (int j = 0; j < dropLength; j += 10) {

			squares1[i].SetPosition(printPos, j);

			window.draw(squares1[i]);

			window.display();

		}

		printPos += squares1[i].GetSideLength();

	}

	printPos = 0;

	//the furthest down on the screen we want to print
	int pos2 = (int) squares2[0].getSize().x * 49;


	for (int i = 0; i < 50; i++) {

		//start at (0,0), move right 1 side length each loop
		squares2[i].SetPosition(printPos, pos2);


		int dropLength = squares2[i].GetDropLength();

		//vertical drop loop
		for (int j = pos2; j > (pos2 - dropLength); j -= 10) {

			squares2[i].SetPosition(printPos, j);

			window.draw(squares2[i]);

			window.display();

		}

		printPos += squares2[i].GetSideLength();

	}

	//necessary to keep the window open and not crash the program during/after execution
	while (window.isOpen()) {
		//polling of events.. may find use elsewhere
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
	}

}

void AppWrapper::CirclesPlayground() {


	//Declare a RenderWindow object
	sf::RenderWindow window;

	//returns VideoMode for current display resolution of the device being used
	sf::VideoMode deviceScreenResolution = sf::VideoMode::getDesktopMode();

	//create the window
	this->CreateNewWindow(window, deviceScreenResolution, "Circles Playground");

	//Do the dance
	//currently this one sucks, but will continue to tweak..
	//possibly with more data points or value manipulation

	this->Untitled(window);
}


void AppWrapper::Untitled(sf::RenderWindow &window) {

	//the array of monthly lightning strike data
	Month Year2001[12];
	
	//the array of circles that will correspond to the strike data
	MonthCircle circles[12];

	


	//read the data from the file into the array of month data
	if (InitializeMonthArray(Year2001)) {

		//initialize the circle array with the month data
		InitializeCircleArray(circles, Year2001);
		
		//position variables
		int XPos = 0, YPos = 0, xIncrementVal = (int)(window.getSize().x / 14), yIncrementVal = 20,
			xShiftVal = 15;

		//count varible used to shift back towards the left
		int count = 0;

		//while the YPos is less than the max size of the screen
		while (YPos < (int) window.getSize().y) {

			//draw the circles
			//1 cycle through the for loop = 1 horizonal pass
 			for (int i = 0; i < 12; i++) {

				//set position
				circles[i].setPosition((float)XPos, (float)YPos);
				
				//draw
				window.draw(circles[i]);
				
				//increment the X position
				XPos += xIncrementVal;

				count += 1;

			}


			//increment the Y position
			YPos += yIncrementVal;
			
			//shift our printing to the right by the shift factor
			XPos = xShiftVal;


			if (count < (window.getSize().y) / 2) {

				//increment the shift factor
				xShiftVal += 15;

			}
			else {

				//decrement the shift factor
				xShiftVal -= 15;
			}
			
		}

		//display the window
		window.display();
		
		//necessary to keep the window open and not crash the program during/after execution
		while (window.isOpen()) {
			//polling of events.. may find use elsewhere
			sf::Event event;
			while (window.pollEvent(event))
			{ 
				if (event.type == sf::Event::Closed)
					window.close();
			}
		}
	}else {

		//display error message and pause for acknowledgement
		system("cls");
		cout << "Unable to open file/file not found!" << endl;
		system("pause");

	}

}

bool AppWrapper::InitializeMonthArray(Month passedMonthArray[12]) {
	
	//return control variable
	bool success = false;

	//declare the ifstream that holds the strike data
	ifstream strikeData("lightning-strikes.csv");

	//running longitude total
	double longitudeTotal = 0.0;

	//running latitude total
	double latitudeTotal = 0.0;

	//running strike count	
	int strikeCount = 0;



	if (strikeData.is_open()) {

		//worker variable used to get non-useful information when needed
		string trash = "";
		char ctrash = '\0';

		int currentMonth = 0;
		double currentLongitude = 0.0;
		double currentLatitude = 0.0;

		//header info for the data
		getline(strikeData, trash);
		
		
		//continue to loop until stream reaches the end
		while (!strikeData.eof()) {

			//the longitude
			strikeData >> currentLongitude;

			//the latitude
			strikeData >> ctrash;
			strikeData >> currentLatitude;

			//the year
			strikeData >> ctrash;
			getline(strikeData, trash, ',');

			//the month
			strikeData >> currentMonth;

			//if the title hasn't already been assigned, assign int
			if (passedMonthArray[currentMonth -1].GetMonthTitle() == 0) {

				//compute and assign the averages for the previous month
				//only if we have monthly data to compute
				if (currentMonth > 1) {

					passedMonthArray[currentMonth - 2].SetAvgLongitude((longitudeTotal / strikeCount));

					passedMonthArray[currentMonth - 2].SetAvgLatitude((latitudeTotal / strikeCount));

					passedMonthArray[currentMonth - 2].SetNumberOfStrikes(strikeCount);
				}
				
				//reset the varibles needed for averages
				longitudeTotal = 0.0;
				latitudeTotal = 0.0;
				strikeCount = 0;

				//assign the month number to the current month
				passedMonthArray[currentMonth -1].SetMonthTitle(currentMonth);

			}

			//add one more strike to the current month
			//passedMonthArray[currentMonth -1].SetNumberOfStrikes(passedMonthArray[currentMonth - 1].GetNumberOfStrikes() + 1);
			
			//add to the running totals
			strikeCount += 1;
			longitudeTotal += currentLongitude;
			latitudeTotal += currentLatitude;

		}

		


		//update success for process
		success = true;
	}
	

	//return outcome
	return success;
}


void AppWrapper::InitializeCircleArray(MonthCircle passedCircleArray[12], Month passedMonthArray[12]) {

	
	for (int i = 0; i < 12; i++) {

		//set the max radius of the circle at position i to 1/3 of the number of strikes 
		//in month i
		passedCircleArray[i].SetMaxRadius((float) (passedMonthArray[i].GetNumberOfStrikes() / 75));

		//setting size
		passedCircleArray[i].setRadius(passedCircleArray[i].GetMaxRadius());

		//set outline thickness
		passedCircleArray[i].setOutlineThickness((float) -15);

	}

	//peach to crimson transition
	//outline
	passedCircleArray[0].setOutlineColor(sf::Color(252, 212, 170));
	passedCircleArray[1].setOutlineColor(sf::Color(249, 194, 160));
	passedCircleArray[2].setOutlineColor(sf::Color(246, 177, 150));
	passedCircleArray[3].setOutlineColor(sf::Color(243, 159, 140));
	passedCircleArray[4].setOutlineColor(sf::Color(240, 142, 130));
	passedCircleArray[5].setOutlineColor(sf::Color(237, 125, 120));
	passedCircleArray[6].setOutlineColor(sf::Color(235, 107, 110));
	passedCircleArray[7].setOutlineColor(sf::Color(232, 90, 100));
	passedCircleArray[8].setOutlineColor(sf::Color(229, 72, 90));
	passedCircleArray[9].setOutlineColor(sf::Color(226, 55, 80));
	passedCircleArray[10].setOutlineColor(sf::Color(223, 37, 70));
	passedCircleArray[11].setOutlineColor(sf::Color(220, 20, 60));

	////peach to crimson transition
	//fill
	//passedCircleArray[0].setFillColor(sf::Color(252, 212, 170));
	//passedCircleArray[1].setFillColor(sf::Color(249, 194, 160));
	//passedCircleArray[2].setFillColor(sf::Color(246, 177, 150));
	//passedCircleArray[3].setFillColor(sf::Color(243, 159, 140));
	//passedCircleArray[4].setFillColor(sf::Color(240, 142, 130));
	//passedCircleArray[5].setFillColor(sf::Color(237, 125, 120));
	//passedCircleArray[6].setFillColor(sf::Color(235, 107, 110));
	//passedCircleArray[7].setFillColor(sf::Color(232, 90, 100));
	//passedCircleArray[8].setFillColor(sf::Color(229, 72, 90));
	//passedCircleArray[9].setFillColor(sf::Color(226, 55, 80));
	//passedCircleArray[10].setFillColor(sf::Color(223, 37, 70));
	//passedCircleArray[11].setFillColor(sf::Color(220, 20, 60));

	//setting color
	//teal to pink transition
	/*passedCircleArray[0].setFillColor(sf::Color(39, 227, 205));
	passedCircleArray[1].setFillColor(sf::Color(57, 220, 200));
	passedCircleArray[2].setFillColor(sf::Color(75, 213, 195));
	passedCircleArray[3].setFillColor(sf::Color(92, 206, 190));
	passedCircleArray[5].setFillColor(sf::Color(128, 192, 180));
	passedCircleArray[6].setFillColor(sf::Color(145, 185, 176)); 
	passedCircleArray[7].setFillColor(sf::Color(163, 178, 171));
	passedCircleArray[8].setFillColor(sf::Color(181, 171, 166));
	passedCircleArray[9].setFillColor(sf::Color(199, 164, 161));
	passedCircleArray[10].setFillColor(sf::Color(216, 157, 156));
	passedCircleArray[11].setFillColor(sf::Color(252, 143, 146));*/
	
	//red to blue transition
	/*passedCircleArray[0].setFillColor(sf::Color(42, 110, 253));
	passedCircleArray[1].setFillColor(sf::Color(72, 103, 224));
	passedCircleArray[2].setFillColor(sf::Color(86, 100, 209));
	passedCircleArray[3].setFillColor(sf::Color(101, 96, 195));
	passedCircleArray[4].setFillColor(sf::Color(116, 93, 180));
	passedCircleArray[5].setFillColor(sf::Color(130, 89, 165));
	passedCircleArray[6].setFillColor(sf::Color(145, 85, 151));
	passedCircleArray[7].setFillColor(sf::Color(160, 82, 136));
	passedCircleArray[8].setFillColor(sf::Color(175, 78, 122));
	passedCircleArray[9].setFillColor(sf::Color(190, 75, 107));
	passedCircleArray[10].setFillColor(sf::Color(204, 72, 93));
	passedCircleArray[11].setFillColor(sf::Color(219, 68, 78));*/

	
}


////
//// Testing
////
//for (int i = 0; i < 12; i++) {

//	cout << "Circle: " << i << " Max Radius: " << passedCircleArray[i].GetMaxRadius() << endl;
//	//initialize the circle array with the month data

//}
////
//// Testing
////
	
	/*sf::RectangleShape squares[50];


	sf::RectangleShape rect;

	rect.setSize(sf::Vector2f(50, 40));
	
	rect.setFillColor(sf::Color::White);*/

	
	//pattern for drawing is clear, draw, display

	//for (int i = 0; i < 1000; i++) {

	//	//rect.setPosition(0, i);

	//	window.clear();
	//	
	//	//window.draw(rect);

	//	window.display();
	//	
	//	

	//}

	//
	//Testing
	//
	//while (window.isOpen())
	//{
	//	//polling of events.. may find use elsewhere
	//	sf::Event event;
	//	while (window.pollEvent(event))
	//	{
	//		if (event.type == sf::Event::Closed)
	//			window.close();
	//	}


	//	window.clear();
	//	
	//	window.display();
	//}
	//
	//End Test
	//

	





