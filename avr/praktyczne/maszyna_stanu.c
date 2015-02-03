void (*state)(*void)=state1;//wskaźnik na funkcje


void stan_machine()
{
state;
}

void state1()
{
action();
state=state2;
}
void state2()
{
action2();
state=state1;
}
