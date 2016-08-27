#include <iostream>
#include <cmath>
#include <SFML/System/Time.hpp>

#include "FFTVisitor.hpp"
#include "TransformationComponent.hpp"
#include "MathTypes.hpp"
#include "kiss_fftr.h"


FFTVisitor::FFTVisitor(std::string musicPath)
{
    _buffer.loadFromFile(musicPath);
    _samples = _buffer.getSamples();
    _numSamples = _buffer.getSampleCount();
    _sampleRate = _buffer.getSampleRate();
    _fourierSize = _sampleRate / 60;

    if(_fourierSize % 2 == 1) _fourierSize += 1;

    _sound.setBuffer(_buffer);
    _sound.play();
}

void FFTVisitor::operator()(FFTComponent& component)
{
    sf::Time audioPosition = _sound.getPlayingOffset();
    _currentSample = audioPosition.asSeconds() * _sampleRate;

	if((_currentSample + _fourierSize) > _numSamples || _sound.getStatus() != sf::SoundSource::Playing) {
		return;
	}

    kiss_fft_scalar in[_fourierSize];
    kiss_fft_cpx out[_fourierSize / 2 + 1];

    // Convert to float and apply window
    for(std::size_t i = 0; i < _fourierSize; ++i) {
        in[i] = _samples[_currentSample+i]*0.54-0.46*cos(2*PI*i/(_fourierSize-1));
    }

    kiss_fftr_cfg cfg;
    if((cfg = kiss_fftr_alloc(_fourierSize, 0, NULL, NULL)) != NULL) {
        kiss_fftr(cfg, in, out);
        free(cfg);
        std::size_t bin = 0;
        float amplitude = sqrt(pow(out[bin].r, 2) + pow(out[bin].i, 2));
        auto& tc = component._node.ref().getComponent<TransformationComponent>();

        /****** Insert heilutuskoodi ******/
        tc.rotateY(amplitude*PI/1560000/6);
    } else {
        printf("Kiss FFT allocation failed\n");
        exit(-1);
    }
}