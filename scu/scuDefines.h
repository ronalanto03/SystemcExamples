/**
@file dLatch.h Usefull Macro's definition
@brief Macros that help to read the code of tfoss system
@author Ronald Sulbaran
@date December 2012
@mail ronalanto03@gmail.com
*/

# ifndef SCU_DEFINES_H
# define SCU_DEFINES_H

# ifndef SYSTEMC_H
# error scuDefines.h must be included after including systemc.h
# else


# define SCU_REPORT_FATAL(error)\
SC_REPORT_FATAL("scu",(string("In ")+kind()+": "+name()+"\n"+error).c_str())



# define SCU_BEGIN_NAMESPACE namespace scu{

# define SCU_END_NAMESPACE }



///Initialize port name to report error in systemc kernel
# define SCU_INIT_PORT_NAME(port)\
port(#port)




SCU_BEGIN_NAMESPACE

/********************
this must be compiled
********************/
inline std::string intToString(int num){
	std::stringstream buff;
	buff<<num;
	return buff.str();

}


SCU_END_NAMESPACE

# endif

# endif
