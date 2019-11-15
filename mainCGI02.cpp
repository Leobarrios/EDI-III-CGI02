#include <iostream>
#include <string>
#include <map>

#include <cstdlib>

#include <cstdio>

using namespace std ;

void traductorUri( std::string _str , map< std::string , std::string > &mapa ) {

    std::string key ;
    std::string value ;

    std::string str = _str ;
    std::string equal = "=" ;
    std::string ampersand = "&" ;
    size_t pos = 0 ;

	while( ( pos = str.find( equal ) ) != ( std::string::npos ) ) {

        key = str.substr( 0 , pos ) ;
		str.erase( 0 , pos + equal.length() ) ;
		value = str.substr( 0 , str.find( ampersand ) ) ;
        str.erase( 0 , str.find( ampersand ) + ampersand.length() ) ;

		if ( key != "sbmt1" ){

            mapa[ key ] = value ;
        }
    }

}

void imprimirHTML( std::string _mensaje ){

    std::cout << "Content-type:text/html\r\n\r\n" ;
    std::cout << "<html>\n" ;

    std::cout << "<head>\n" ;
    std::cout << "<title>Hello World - Second CGI program</title>\n" ;
    std::cout << "</head>\n" ;

    std::cout << "<body>\n" ;
    std::cout << "<form action='tp2-cgi.exe' method='post'>" ;
    std::cout << "<label>Introduzca su nombre:</label>\n" ;
    std::cout << "<input type='text' name='txt1' id='text1'>\n" ;
    std::cout << "<input type='submit' name='sbmt1' value='enviar'>\n" ;
    std::cout << "</form>\n" ;

    std::cout << _mensaje ;

    std::cout << "</body>\n" ;
    std::cout << "</html>\n" ;


}

// MÉTODO GET
const char* getGetdata(){

    const char* elemento_GET = getenv( "QUERY_STRING" ) ;

    return elemento_GET ;
}

const char* getPostdata(){

    int len = atoi( getenv( "CONTENT_LENGTH") ) ;
    char *postdata = new char( len ) ;
    fgets( postdata, len, stdin ) ;

    return postdata ;
}

std::string getMensaje() {

    const char* elemento_GET = getPostdata() ;

    if ( elemento_GET != NULL && elemento_GET[0] != '\0' ) {

        map < std::string , std::string > map2 ;

        traductorUri( elemento_GET , map2 ) ;

        if ( map2[ "txt1" ].empty() ) {

            return "Escriba un nombre para continuar." ;
        }
        else {

			return "<h2>Hello! " + map2["txt1"] + " This is my Refactoring 01 CGI program.</h2>\n" ;
		}

    }

    return "" ;

}



int main(int argc, char *argv[])
{

    imprimirHTML( getMensaje() ) ;

    return 0;
}
