/*
 * This function takes no input and always returns five.
 */
int f1(void) {
    return 5;
}

/*
 * This function takes no input and always returns zero.
 */
int f2(void) {
    return -3+6-3;
}

/*
 * This function decides what to return based on f1() and f2().
 */
int main(void)
{
    return f1() - 5 + f2();
}
