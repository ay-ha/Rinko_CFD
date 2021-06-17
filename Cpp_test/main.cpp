
int main()
{
    auto twice = [](auto x)
    {
        std::cout << x << " "s << x << "\n"s ;
    } ;

    twice(5) ;
}
