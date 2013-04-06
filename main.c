/*
 * This function takes no input and always returns five.
 */
int f1(void) {
    return 4;
}

/*
 * This function takes no input and always returns zero.
 */
int f2(void) {
    return 0;
}

/*
 * This function decides what to return based on f1() and f2().
 */
int main(void)
{
    return f1() - 5 + f2();
}
