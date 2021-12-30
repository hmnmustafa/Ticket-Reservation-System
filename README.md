# Ticket-Reservation-System
by Hamna Mustafa

In this project, I created a ticket reservation system in C++. A seating chart for an auditorium is provided in a txt file. An example file looks like:

<img width="155" alt="Screen Shot 2021-12-30 at 4 53 25 AM" src="https://user-images.githubusercontent.com/42907026/147747939-3fba7f3d-57fa-4c14-8b1a-e063425becf6.png">


Each line represents one row of the auditorium. The "." represent empty seats where as "A","C","S" represent reserved seats for adults, children, and seniors respectively. 

I designed a grid using a 4-way linked list in C++ that represented a seating chart for an auditorium using the text file.
I then displayed the seating chart to users and allowed them to reserve seats and found the best seats available if the user’s chosen seats were occupied. The best seats available were calculated by finding the seats whose midpoint is closest to the midpoint of the row. 
If the user decides to reserve the seats, the code updates the text file so that the reserved seats for the auditorium are updated. The user is then given the option to reserve more seats or exit the program. 
Once the user exits, a report is generated that calculates and displayes ticket sales’ statistics.

# Sample Run

The words in bold are the output of the program whereas the words not in bold are the input by the user.

<img width="841" alt="Screen Shot 2021-12-30 at 5 25 04 AM" src="https://user-images.githubusercontent.com/42907026/147747735-fbb83c9e-dd07-49bc-9e7d-faf267ca710c.png">

<img width="860" alt="Screen Shot 2021-12-30 at 5 26 22 AM" src="https://user-images.githubusercontent.com/42907026/147747837-020c853f-5e2d-4f9a-acd3-c20a8eb7181a.png">


