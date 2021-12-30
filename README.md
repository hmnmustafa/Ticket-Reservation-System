# Ticket-Reservation-System
by Hamna Mustafa

In this project, I created a ticket reservation system in C++. A seating chart for an auditorium is provided in a txt file. An example file looks like:

<img width="148" alt="Screen Shot 2021-12-30 at 5 56 00 AM" src="https://user-images.githubusercontent.com/42907026/147749947-bf2d6938-bf99-45fb-9900-5048bc811f5e.png">


Each line represents one row of the auditorium. The "." represent empty seats where as "A","C","S" represent reserved seats for adults, children, and seniors respectively. 

I designed a grid using a 4-way linked list in C++ that represented a seating chart for an auditorium using the text file.
I then displayed the seating chart to users and allowed them to reserve seats and found the best seats available if the user’s chosen seats were occupied. The best seats available were calculated by finding the seats whose midpoint is closest to the midpoint of the row. 
If the user decides to reserve the seats, the code updates the text file so that the reserved seats for the auditorium are updated. The user is then given the option to reserve more seats or exit the program. 
Once the user exits, a report is generated that calculates and displayes ticket sales’ statistics.

# Sample Run

The words in bold are the output of the program whereas the words not in bold are the input by the user.

<img width="776" alt="Screen Shot 2021-12-30 at 5 56 47 AM" src="https://user-images.githubusercontent.com/42907026/147749974-f261168b-f9df-4ee8-9998-98fd0c050fda.png">
<img width="850" alt="Screen Shot 2021-12-30 at 5 57 02 AM" src="https://user-images.githubusercontent.com/42907026/147749990-639a243f-1863-4e93-b80d-235509605bd7.png">


