# Fitness-Club
A simple database management system for a fitness club. 
The system maintains records for members of a fitness club. Each record contains name, age,
height, and current Body Mass Index (BMI), and the weight group (e.g., underweight, normal,
overweight) based on BMI. If a member’s weight info has been updated, then a history of weight
groups is maintained.

Body mass index, or BMI, is a number based on a person’s weight and height. It is a way to help
figure out if a person is at a healthy weight for his/her height. In general, the higher the number,
the more body fat a person has. BMI is often used as a screening tool to decide if a person’s
weight might be putting him/her at risk for health problems.

The database maintains a collection of member records. Each member record is naturally implemented
as a structure, and contains the following information fields:
- name of type char [] , which represents the patient’s name
- int age, which represents the patient’s age
- int height, which represents the member’s height (in cm)
- float BMI, which represents the member’s Body mass index (BMI)
- status of type char [], which represents the member’s weight group bases on BMI.

Programmatically, the database maintains an array of pointers to record structs.

The program will provide several basic functionalities:
- Accepting entry of a new member record into the current database, and generating weight
- group information for the member.
- Displaying all records in the current database
- Removing an existing member’s record in the current database
- Updating weight info of an existing member, and generating new weight group for the member
- Sorting the records in the current database
- Clearing the current database

Specifically, the program keeps on prompting the user with the following menu, until q or Q is
chosen, which terminates the program.
