#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <tuple>
#include <cassert>

template<typename uniq_type0 , typename uniq_type1>

auto primitive_compare(uniq_type0 identificator1, uniq_type1 identificator2)
{
    try
    {
        decltype(identificator1) variable1  = identificator1;
        decltype(identificator2) variable2  =  identificator2;
     
  
        if constexpr (std::is_same_v<uniq_type0,uniq_type1>)
        {
            if(variable1 == variable2) return true;
            else return false;
        }
        else return false;
    }
    catch(...)
    {
        return false;
    }

}

template<typename uniq_type0 , typename uniq_type1>

constexpr bool is_same_types(uniq_type0  variable1 , uniq_type1 variable2)
{
    return std::is_same_v<uniq_type0 , uniq_type1>;
}

auto compare_logicIPV = [](const std::vector<std::string>& a, const std::vector<std::string>& b) 
{
    return std::make_tuple(std::stoi(a[0]), std::stoi(a[1]), std::stoi(a[2]), std::stoi(a[3])) >
           std::make_tuple(std::stoi(b[0]), std::stoi(b[1]), std::stoi(b[2]), std::stoi(b[3]));
};


bool vectors_equal(const std::vector<std::string>& v1, const std::vector<std::string>& v2)
{
    if(v1.size() != v2.size()) 
        return false;
    
    for(size_t i = 0; i < v1.size(); i++)
    {
        if(v1[i] != v2[i]) 
            return false;
    }
    
    return true; 
}



std::vector<std::string> split(const std::string &str, char d)
{
    std::vector<std::string> r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while(stop != std::string::npos)
    {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}

auto ip_to_tuple(const std::vector<std::string>& ip_parts)
{
    return std::make_tuple(
        std::stoi(ip_parts[0]),
        std::stoi(ip_parts[1]), 
        std::stoi(ip_parts[2]),
        std::stoi(ip_parts[3])
    );
}

int main()
{
    try {
        std::vector<std::vector<std::string>> ip_pool;
        std::ifstream file("ip_filter.txt");
        
        if (!file.is_open()) {
            std::cerr << "Error: Cannot open ip_filter.tsv" << std::endl;
            return 1;
        }
        
        
    
        std::string line;
        while (std::getline(file, line)) 
        {    
            std::vector<std::string> parts = split(line, '\t');
            std::vector<std::string> ip_parts = split(parts[0], '.');
            ip_pool.push_back(ip_parts);
        }
        

      

        std::sort(ip_pool.begin(), ip_pool.end(),compare_logicIPV);

        std::cout << std::endl;

        std::cout << " IPs with first byte  1 " << std::endl;
        
        for(const auto& ip : ip_pool) {
            if(std::stoi(ip[0]) == 1) {
                std::cout << ip[0] << "." << ip[1] << "." << ip[2] << "." << ip[3] << std::endl;

            }
        }
        
        
        std::cout << std::endl;

        std::cout << "=== IPs with first byte = 46 and second = 70 ===" << std::endl;
        for(const auto& ip : ip_pool) {
            if(std::stoi(ip[0]) == 46 && std::stoi(ip[1]) == 70) {
                std::cout << ip[0] << "." << ip[1] << "." << ip[2] << "." << ip[3]<<std::endl;
            }
        }
        

        std::cout << std::endl;

        std::cout << "=== First  IPs with any byte = 46 ===" << std::endl;
     
        for(const auto& ip : ip_pool) {
            for(const auto& part : ip) {
                if(std::stoi(part) == 46) 
                {
                        std::cout << ip[0] << "." << ip[1] << "." << ip[2] << "." << ip[3] << std::endl;
                }
            }
        }

        
    } catch(const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    
    const std::vector<std::string> v1 = {"1","2","3","4"};
    const std::vector<std::string> v2 = {"1","3","4","4"};
    assert(vectors_equal(v1,v2) == false);
    
    const std::vector<std::string> v3 = {"1","2","3","4","5"};
    const std::vector<std::string> v4 = {"1","2","3","4","5"};
    assert(vectors_equal(v3,v4) == true);

    const std::string str = "223.22.43.1";
    std::vector<std::string> expected = {"223","22","43","1"};
    assert(vectors_equal(split(str, '.'), expected) == true);

    const std::string str1 = "24.211.24.12";
    std::vector<std::string> expected1 = {"24","211","24","12"};
    assert(vectors_equal(split(str1,'.'),expected1) == true);

    const std::string str2 = "218.192.64.1";
    std::vector<std::string> expected2 = {"90","45","211","3"};
    assert(vectors_equal(split(str2,'.'),expected2) == false);

    
    assert(primitive_compare(10 , "10") == false);
    assert(primitive_compare(10 ,10) == true);
    assert(primitive_compare("10","10") == true);
    assert(primitive_compare('10',"10") == false);

    assert(is_same_types(109 , 110) == true);
    assert(primitive_compare(109, 110) == false);

    std::vector<int> vector_0 = {};
    std::vector<int> vector_1 = {};

    assert(is_same_types(vector_0 , vector_1) == true);

    assert(is_same_types(std::string("Hello") , std::string ("World")) == true);




    std::cout << "All tests passed!" << std::endl;
    return 0;
}