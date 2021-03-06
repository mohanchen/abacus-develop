#include "../src_pw/tools.h"
#include "../src_pw/global.h"
#include "hamilt_linear.h"
#include "sltk_atom_arrange.h"
#include "use_overlap_table.h"
#include "grid_integral.h"
#include "build_st_pw.h"

Hamilt_Linear::Hamilt_Linear()
{}

Hamilt_Linear::~Hamilt_Linear()
{
	if(test_deconstructor)
	{
		cout << " ~Hamilt_Linear()" << endl;
	}
}

void Hamilt_Linear::set_orb_tables(void)
{
    TITLE("Hamilt_Linear","set_orb_tables");
	timer::tick("Hamilt_Linear","set_orb_tables",'B');
    
	//xiaohui modify 2013-09-02
	//if(!LINEAR_SCALING) 
	//{
	//	timer::tick("Hamilt_Linear","set_orb_tables",'B');
	//	return; //mohan add 2009-12-22
	//} xiaohui modify 2013-09-02. Attention...
	
	//=============================================================================
    // (1) FUNCTION : use 'info' to generate 'Numerical Orbital'
    // (1) RESULT : We have 'Numerical Orbital' for calculate S-table and T-table.
	//=============================================================================
    ORB.Read_Orbitals();

	if(CALCULATION=="test")
	{
		timer::tick("Hamilt_Linear","set_orb_tables",'B');
		return;
	}

    //=============================================================================
    // (2) FUNCTION : Generate Gaunt_Coefficients and S-table using UOT.init
    // 	   Must have 'Numerical Orbital' infomation
    // (2) RESULT : we have tabulated S table for use.
    //=============================================================================
    const int job0 = 3;
    // job0 :
    // 1: generate overlap table
    // 2: generate kinetic table
    // 3: generate overlap & kinetic table
    UOT.gen_tables(job0);
    // init lat0, in order to interpolated value from this table.
    UOT.set_unit(ucell.lat0);


	timer::tick("Hamilt_Linear","set_orb_tables",'B');
    return;
}

void Hamilt_Linear::clear_after_ions()
{
    TITLE("Hamilt_Linear","clear_after_ions");
    UOT.MOT.Destroy_Table();
    UOT.MOT.Destroy_Table_Beta();
    return;
}
