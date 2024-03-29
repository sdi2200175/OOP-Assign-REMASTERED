## Εγχειρίδιο Συστήματος Διαχείρησης Πανεπιστημιακού Τμήματος
Εργασία στον Αντικειμενοστραφή Προγραμματισμό Μέρος Β'


### Α. Κεντρικό Μενού
Στο κεντρικό μενού υπάρχουν επιλογές για την διαχείρηση των μαθητών, καθηγητών και μαθημάτων του τμήματος καθώς και η δυνατότητα αποθήκευσης των στοιχείων της γραμματείας σε αρχεία αλλά και η δυνατότητα μετακίνησης του τμήματος στο επόμενο εξάμηνο.

#### 1. Διαχείρηση Μαθητών
- Στην διαχείρηση μαθητών μπορείτε να προσθέσετε, διαγράψετε και αλλάξετε τα στοιχεία ενός μαθητή. Συγκεκριμένα, μπορείτε να μεταβάλλετε τα στοιχεία που δεν σχετίζονται με την ακαδημαϊκή πρόοδο του φοιτητή, καθώς τα στοιχεία αυτά διαχειρίζονται εξ'ολοκλήρου από την γραμματεία και καθορίζονται από τους βαθμούς τους και τα μαθήματα που έχουν ολοκληρώσει. 

- Μπορείτε επιπλέον να εγγράψετε κάποιον μαθητή σε ένα συγκεκριμένο μάθημα, να εκτυπώσετε την βαθμολογία του για όποιο εξάμηνο θέλετε, αλλά και να δείτε επι τόπου αν μπορεί να αποκτήσει πτυχίο.

#### 2. Διαχείρηση Καθηγητών
- Στην διαχείρηση καθηγητών μπορείτε να προσθέσετε, διαγράψετε και αλλάξετε τα στοιχεία ενός καθηγητή. Συγκεκριμένα, μπορείτε να μεταβάλλετε τα στοιχεία που δεν σχετίζονται με τα αναθεμένα μαθήματα του καθηγητή.

- Επιπλέον, μπορείτε μέσω του μενού αυτού να καταθέσετε βαθμολογία για κάποιο συγκεκριμένο μάθημα, να δείτε τα στατιστικά του καθηγητή για όλα τα μαθήματα στα οποία διδάσκει και να αναθέσετε σε κάποιον καθηγητή κάποιο συγκεκριμένο μάθημα.

#### 3. Διαχείρηση Μαθημάτων
- Στην διαχείρηση μαθήματος μπορείτε να προσθέσετε, διαγράψετε και αλλάξετε τα στοιχεία ενός μαθήματος. __Προσοχή:__ Δεν επιτρέπετε να αλλάξετε στοιχεία ενός μαθήματος ή να διαγράψετε ένα μάθημα εάν αυτό παρακολουθείται από μαθητές ή/και έχει ανατεθεί σε καθηγητή.

- Από το μενού αυτό μπορείτε επίσης να εγγράψετε κάποιον μαθητή σε κάποιο μάθημα, να αναθέσετε κάποιο μάθημα σε κάποιον καθηγητή αλλά και να αποθηκεύσετε τους μαθητές που πέρασαν ένα συγκεκριμένο μάθημα σε κάποιο συγκεκριμένο εξάμηνο σε ένα εξωτερικό αρχείο.

#### 4. Έλεγχος Δυνατότητας Απόκτησης Πτυχίου
- Μπορείτε να δείτε ποιοί μαθητές του τμήματος δικαιούνται με βάση τις αρχικά εισαγμένες παραμέτρους να λάβουν το πτυχίο τους.

#### 5. Αλλαγή Εξαμήνου
- Μπορείτε να μεταβάλλετε το τμήμα στο επόμενο εξάμηνο. Αυτή η διαδικασία αφαιρεί τους καθηγητές και τους μαθητές από κάθε μάθημα. __Προσοχή:__ Για να γίνει αυτή η διαδικασία, απαιτείται να έχουν βαθμολογηθεί πρώτα όλοι οι φοιτητές στα μάθηματα στα οποία είναι εγκεγραμμένοι.

### Β. Makefile
Το Makefile που περιλαμβάνεται υλοποιεί τις παρακάτω λειτουργίες:

- __make all:__ Δημιουργεί το τελικό εκτελέσιμο αρχείο "UniManagement-1.0.exe" και καθαρίζει όλα τα object files που χρειάστηκε να φτιαχτούν.

- __make run:__ Τρέχει το εκτελέσιμο. Αν το εκτελέσιμο δεν υπάρχει, τρέχει το make all.

- __make clean:__ Διαγράφει ότι αρχεία μπορεί να έχουν απομείνει απο το compile, μαζί και το εκτελέσιμο.

- __make valgrind:__ Κάνει compile το εκτελέσιμο και το τρέχει μέσω του valgrind memory check.

### Γ. Βάση Δεδομένων
- Το πρόγραμμα χρησιμοποιεί τα αρχεία "student_db", "professor_db" και "course_db" ως βάσεις δεδομένων. Εκεί αποθηκεύει αντίστοιχα τους μαθητές τους καθηγητές και τα μαθήματα και από τα αρχεία αυτά διαβάζει τις πληροφορίες αυτές όταν ανοίγει. Αν τα αρχεία λείπουν, το πρόγραμμα τρέχει κανονικά, απλά χωρίς μαθητές καθηγητές και μαθήματα. Ωστόσο, κατά την έξοδο, θα φτιαχτούν νέα τέτοια αρχεία για την αποθήκευση. Τα αρχεία αυτά βρίσκονται στον φάκελο data, __ο οποίος δεν πρέπει να διαγραφθεί σε καμία περίπτωση__ καθώς χρησιμοποιείται για αποθήκευση, η οποία θα αποτύχει αν ο φάκελος δεν υπάρχει.

### Δ. Credits
Η εργασία έγινε από τους φοιτητές Ευαγγελία Ραγκούση με Αριθμό Μητρώου 1115202200154 και Σπύρος Στρακόσια με Αριθμό Μητρώου 1115202200175.