#ifndef FFT_VISITOR_HPP
#define FFT_VISITOR_HPP

#include <cstddef>
#include <SFML/Audio.hpp>

#include "Visitor.hpp"
#include "FFTComponent.hpp"

class FFTVisitor : public Visitor<FFTVisitor, FFTComponent> {
public:
    FFTVisitor(std::string musicPath);

    void operator()(FFTComponent& component);
private:
	sf::SoundBuffer _buffer;
    const sf::Int16* _samples;
    std::size_t _currentSample;
    std::size_t _numSamples;
    std::size_t _fourierSize;
    unsigned _sampleRate;
    sf::Sound _sound;
};

#endif