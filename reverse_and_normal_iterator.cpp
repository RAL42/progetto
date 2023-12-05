#include<iostream>
#include<vector>

int main(){
    std::vector<int> vec{1,2,3,4};
/*
    for (auto i = vec.rbegin(); i != vec.rend(); i++)
    {
        std::cout<<*i <<std::endl;    
    }

    std::cout<<"-----------------------" << std::endl;

for (auto i = vec.begin(); i != vec.end(); i++)
{
    std::cout<< *i <<std::endl;
}

    std::cout<<"-----------------------" << std::endl;

std::cout<< *(vec.end() - 2) << std::endl;
    
std::cout<< vec.back()  << std::endl;
*/
std::cout<< "size = " << vec.size() << std::endl;

std::cout<< "vec[vec.size()-1] = " << vec[vec.size()] << '\n';
    
    
}