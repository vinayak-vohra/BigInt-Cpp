// #include "classes/BigInt.cpp"
// #include <chrono>
// #include <iomanip>

// Driver code
int main()
{
    // Uncomment below lines for custom input

    // string s1, s2;           // declare two strings
    // cout << "Enter Num 1: "; // prompt for num 1
    // cin >> s1;               // input num 1
    // cout << "Enter Num 2: "; // prompt for num 2
    // cin >> s2;               // input num 1
    // BigInt X(s1);            // Init Num 1
    // BigInt Y(s2);            // Init Num 2
    // BigInt Z = X * Y;        // Calculate product
    // cout << Z << endl;       // Print Product

    // ---------------------------------------- //

    // Uncomment below lines to run sample on two 8-digit numbers

    // BigInt A("99999999"); // Init Num 1
    // BigInt B("99999999"); // Init Num 2
    // BigInt C = A * B;     // Multiply
    // cout << C << endl;    // Print Product

    // ---------------------------------------- //

    // Uncomment below lines to check time to multiply two 10-digit numbers
    // *Requirements:
    //   c++ 11 or above   : for auto keyword
    //   <chrono> library  : for time calulation
    //   <iomanip> library : for output time precision

    // BigInt D("9999999999");                            // Init Num 1
    // BigInt E("9999999999");                            // Init Num 2
    // auto start = chrono::high_resolution_clock::now(); // Note start time
    // BigInt F = D * E;                                  // Perform multiplication
    // auto end = chrono::high_resolution_clock::now();   // Note end time
    // double time_taken =                                // convert time to seconds
    //     chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    // time_taken *= 1e-9; // for precision
    // cout << F << endl;  // Prints 99999999980000000001
    // cout << "Time Taken: " << fixed << setprecision(9) << time_taken << "sec";

    // ---------------------------------------- //

    // Use below line to check memory usage
    // cout << mem_usage << endl;

    // ****** Note ******
    // mem_usage is not accurate.
    // Actual memory usage may be higher
    // than the displayed value.
}