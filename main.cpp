int main()
{
    int clock = 0; 

    for(int i = 0; i < 3000; i++) {

        

        if(clock == 0) {
            clock = 1; 
        } else {
            clock = 0;
        }
    }
    return 0;
}