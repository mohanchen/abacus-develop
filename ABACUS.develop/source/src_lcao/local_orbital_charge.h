#ifndef LOCAL_ORBITAL_CHARGE
#define LOCAL_ORBITAL_CHARGE

#include "src_pw/tools.h"
#include "src_lcao/grid_technique.h"

#include "src_lcao/wfc_dm_2d.h"

class Local_Orbital_Charge
{
public:
	friend class Trace_Rho_HS;

	Local_Orbital_Charge();
	~Local_Orbital_Charge();

	void allocate_gamma(const Grid_Technique &gt);
	void allocate_DM_k(void);
	void sum_bands(void);

	//liaochen modify on 2010-3-23 
	//change its state from private to public
	double*** DM;	
	complex<double>*** DM_B; //density matrix in B field, Zhiyuan add 2012-01-13//
	double** DM_R;

	void write_dm(const int &is, const int &iter, const string &fn, const int &precision);
	int out_dm; // output density matrix or not.
	void read_dm(const int &is, const string &fn);
	
	Wfc_Dm_2d wfc_dm_2d;		// Peize Lin test 2019-01-16

private:

	bool init_DM;
	bool init_DM_R;

	void cal_dk_gamma(void);
	void cal_dk_k(const Grid_Technique &gt);

	int test;
	// mohan add 2010-09-06
	int lgd_last;// sub-FFT-mesh orbitals number in previous step.
	int lgd_now;// sub-FFT-mesh orbitals number in this step.

	int nnrg_last;// sub-FFT-mesh orbtials number in previous step, with k.
	int nnrg_now; // sub-FFT-mesh orbitals number in this step, with k.

	// add by yshen on 9/22/2014
	// these variables are memory pool for DM series matrixes, so that these matrixes will be storaged continuously in the memory.
	double **DM_pool;
	complex<double> **DM_B_pool;
	
	// Buffer parameters for tranforming 2D block-cyclic distributed DM matrix 
	// to grid distributed DM matrix
    int *sender_2D_index;
    int sender_size;
    int *sender_size_process;
    int *sender_displacement_process;
    double* sender_buffer;

    int *receiver_local_index;
    int receiver_size;
    int *receiver_size_process;
    int *receiver_displacement_process;
    double* receiver_buffer;

    int setAlltoallvParameter(MPI_Comm comm_2D, int blacs_ctxt, int nblk);
    void cal_dk_gamma_from_2D(void);
};

#endif
