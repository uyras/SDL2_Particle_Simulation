//
// Created by Andrei Vasilev on 1/13/17.
//

#include "Swarm.h"

namespace ps {

    Swarm::Swarm() : last_clock(0) {
        double dx=1/50.;
        m_particle_array = new Particle[N_PARTICLES];
        for (int i=0; i< 100; ++i){
            for (int j=0; j< 100; ++j){
                m_particle_array[i*100+j].m_x_cord = i*dx-1;
                m_particle_array[i*100+j].m_y_cord = j*dx-1;
            }
        }
        m_particle_array[0].state=2;
        m_particle_array[1].state=2;
        m_particle_array[2].state=2;
        m_particle_array[3].state=2;
    }


    Swarm::~Swarm() {
        delete [] m_particle_array;
    }


    void Swarm::move(int elapsed) {
       /* Interval between last particle position update and current update is used
        * to ensure that particle movement stays consistent and proportional to the
        * amount of time between updates. Helps to maintain smooth movement. During
        * the first actual update interval is kept at zero to prevent a large particle
        * position jump from occurring. */
        if(last_clock == 0)
            interval = 0;
        else
            interval = elapsed - last_clock;

        last_clock = elapsed;

        // Update all particle positions within the swarm.
        for(int i = 0; i < N_PARTICLES; ++i)
            m_particle_array[i].move_particle(interval);
    }


    const Particle * const Swarm::get_particles() {
        return m_particle_array;
    }

    void Swarm::burn_step() {
        unsigned s0=0,s1=0,s2=0;
        double r2 = radius*radius,dst;
        for(int i = 0; i < N_PARTICLES; ++i) {
            if (m_particle_array[i].state==0)
                ++s0;
            if (m_particle_array[i].state==1)
                ++s1;
            if (m_particle_array[i].state>1){
                ++s2;

                //extinguish neighbours
                for (int j =0; j< N_PARTICLES; ++j){
                    if (m_particle_array[j].state == 0 && i!=j && (dst=distance(
                            m_particle_array[i].m_x_cord,
                            m_particle_array[i].m_y_cord,
                            m_particle_array[j].m_x_cord,
                            m_particle_array[j].m_y_cord
                            )) <= r2){
                        m_particle_array[j].temp_state=2;
                    }
                }

                //update itself
                m_particle_array[i].temp_state = m_particle_array[i].state+1;

                //distinguish itself if needed
                if (m_particle_array[i].temp_state >= burnSteps+2){
                    m_particle_array[i].temp_state = 1;
                }
            }
        }
        this->adjustStates();
        //std::cout<<s0<<"\t"<<s1<<"\t"<<s2<<"\t"<<std::endl;
    }

    double Swarm::distance(double x1, double y1, double x2, double y2) {
        return (x1-x2)*(x1-x2)+(y1-y2)*(y1-y2);
    }

    void Swarm::adjustStates() {

        for(int i = 0; i < N_PARTICLES; ++i) {
            m_particle_array[i].state = m_particle_array[i].temp_state;
        }
    }


} /* namespace ps */
