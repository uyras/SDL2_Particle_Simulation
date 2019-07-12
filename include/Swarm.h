//
// Created by Andrei Vasilev on 1/13/17.
//

#ifndef PARTICLE_SIMULATION_SWARM_H
#define PARTICLE_SIMULATION_SWARM_H

#include "Particle.h"
#include <iostream>

namespace ps {

    class Swarm {
        public:
            const static int N_PARTICLES{10000};  // Change to adjust particle count.

        public:
            Swarm();
            virtual ~Swarm();
            void move(int);
            const Particle * const get_particles();
            void burn_step();


        private:
            Particle *m_particle_array { nullptr };
            int last_clock;
            int interval;

            static double distance(double x1,double y1,double x2, double y2);
            void adjustStates();

            const double radius = 0.03;
            const double burnSteps=2;
    };

} /* namespace ps */

#endif //PARTICLE_SIMULATION_SWARM_H
