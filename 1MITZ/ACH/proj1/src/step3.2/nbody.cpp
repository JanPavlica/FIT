/*
 * Architektura procesoru (ACH 2016)
 * Projekt c. 1 (nbody)
 * Login: xpavli78
 */

#include "nbody.h"

void particles_simulate(t_particles &p)
{
    
    int i, j, k;

    t_velocities velocities;

    for (k = 0; k < STEPS; k++)
    {
            //vynulovani mezisouctu
        for (i = 0; i < N; i++)
        {
            velocities.x[i] = 0.0f;
            velocities.y[i] = 0.0f;
            velocities.z[i] = 0.0f;
        }
            //vypocet nove rychlosti
        for (i = 0; i < N; i++)
        {
            #pragma omp simd
            for (j = 0; j < N; j++)
            {
                __assume_aligned(&p, 64);
                calculate_both_velocities(p.pos_x[j], p.pos_y[j], p.pos_z[j], p.vel_x[j], p.vel_y[j], p.vel_z[j], p.weight[j], p.pos_x[i], p.pos_y[i], p.pos_z[i], p.vel_x[i], p.vel_y[i], p.vel_z[i], p.weight[i], &velocities.x[j], &velocities.y[j], &velocities.z[j]);
            }
        }
            //ulozeni rychlosti a posun castic
        for (i = 0; i < N; i++)
        {
            p.vel_x[i] += velocities.x[i];
            p.vel_y[i] += velocities.y[i];
            p.vel_z[i] += velocities.z[i];
            
            p.pos_x[i] += p.vel_x[i] * DT;
            p.pos_y[i] += p.vel_y[i] * DT;
            p.pos_z[i] += p.vel_z[i] * DT;
        }
    }
}


void particles_read(FILE *fp, t_particles &p)
{
    for (int i = 0; i < N; i++)
    {
        fscanf(fp, "%f %f %f %f %f %f %f \n",
            &p.pos_x[i], &p.pos_y[i], &p.pos_z[i],
            &p.vel_x[i], &p.vel_y[i], &p.vel_z[i],
            &p.weight[i]);
    }
}

void particles_write(FILE *fp, t_particles &p)
{
    for (int i = 0; i < N; i++)
    {
        fprintf(fp, "%10.10f %10.10f %10.10f %10.10f %10.10f %10.10f %10.10f \n",
            p.pos_x[i], p.pos_y[i], p.pos_z[i],
            p.vel_x[i], p.vel_y[i], p.vel_z[i],
            p.weight[i]);
    }
}
