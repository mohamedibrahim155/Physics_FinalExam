#pragma once

#include <random>

static const float GetRandomFloatNumber(float minValue, float maxValue)
{
	std::random_device rd;  
	std::mt19937 gen(rd()); 
	std::uniform_real_distribution<float> distribution(minValue, maxValue); 

	return distribution(gen);
}

static const int GetRandomIntNumber(int minValue, int maxValue)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> distribution(minValue, maxValue);

	return distribution(gen);
}

static const glm::vec3 GetRandomDirection()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(0.0, 1.0);

    // Generate random values for the components
    float randomX = dis(gen);
    float randomY = dis(gen);
    float randomZ = dis(gen);

    // Create a vector with random components
    glm::vec3 randomVector = { randomX, randomY, randomZ };

    // Normalize the vector and return it
    return normalize(randomVector);
}


static const glm::vec3 GetRandomPoint1()
{
    //int x = GetRandomIntNumber(-53, 53);
    //int y = GetRandomIntNumber(-26, 26);
    //int z = GetRandomIntNumber(-80, 80);

    int x = GetRandomIntNumber(-53, -25);
    int y = GetRandomIntNumber(-10, 30);
    int z = GetRandomIntNumber(-80, -25);

   

    return glm::vec3(x, y, z);
}


static const glm::vec3 GetRandomPoint2()
{
    //int x = GetRandomIntNumber(-73, -53);
    //int y = GetRandomIntNumber(-46, -26);
    //int z = GetRandomIntNumber(-100, -80);

    int x = GetRandomIntNumber(25, 53);
    int y = GetRandomIntNumber(-10, 30);
    int z = GetRandomIntNumber(25, 80);

    return glm::vec3(x, y, z);
}