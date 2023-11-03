As part of the first project of the Algorithms and Data Structures course, a system was proposed for managing L.EIC class schedules, which allows viewing various pieces of information, managing student requests and canceling unwanted actions.

This project was carried out by students from group 23: Duarte Souto Assunção, Guilherme Duarte Silva Matos and João Vítor da Costa Ferreira.

---

# Getting Started
The project was developed in C++ and uses the CMake tool to compile the source code and this documentation.
### Using the terminal
```
cmake CMakeLists.txt
make
./AED2324_PRJ1_G23 -cpu classes_per_uc.csv -c classes.csv -sc students_classes.csv
```

> **Warning:** Don't forget to **change the location of the csv files in the terminal commands**.  
> The commands above assume that the csv files are in the same directory as the executable.

> **Note:** Each flag indicates a file that must be passed as an argument to the program.
> - `-cpu` is the file containing the UCs and classes.
> - `-c` is the file containing every lesson for every class.
> - `-sc` is the file containing every student and their corresponding classes.

### Using CLion
1. Open the project folder in CLion.
2. Edit or add the configuration `AED2324_PRJ1_G23` with the correct program arguments and working directory.  
   For example:
    - Program arguments: `-cpu schedule/classes_per_uc.csv -c schedule/classes.csv -sc schedule/students_classes.csv`
    - Working directory: `~/AED2324_PRJ1_G23`
3. Run the configuration.

------

# Usage
The _SchedulEd_ interface offers the following options:

### Listing
- `print student <student_code>` | Shows information about a student, including their name, classes enrolled and schedule.
- `print uc <uc_code>` | Shows information about a UC, including their classes and number of students enrolled in each one.
- `print class <uc_code> <class_code>` | Shows information about a class, including their students and schedule.
- `student_count` | Counts the total number of students inside the database.
- `student_list [<first_position> <number_of_students>]` | Lists all students in the database, starting at the given position and showing the given number of students. If no arguments are given, it lists all students.

### Requests
Some requests may be accepted, rejected or cause conflicts, depending on the current state of the database.
- `add <student_code> <uc_code> <class_code>` | 
- `remove <student_code> <uc_code>`
- `switch <student_code> <student_code> <uc_code>`
- `undo`

### Control
- `save`
- `quit`
- `help`
