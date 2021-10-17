// 10527142
# include <stdio.h>
# include <cstdlib> 
# include <vector>
# include <iostream>
# include <string>

using namespace std ;

struct TokenData{
  string name ;
  string type ;
  string constantType ;
  int whereLine ;
  int whereColum ;
} ; 

struct IDENTData{
  string name ;
  string type ; 
  string constant ;
  int valueI ;
  float valueF ;
} ;

struct FunctionInfo{
  string functionName ;
  vector<IDENTData> functionID ;
  vector<TokenData> functionToken ;
} ;

vector<TokenData> gInput ;
vector<IDENTData> gIDList ;
vector<IDENTData> gIDTemp ;
vector<FunctionInfo> gFunction ;

int gInputHead = 0 ;

// ------------------------------------------------------------------
bool IsStringOnlyNumDot( string name ) ;
bool IsStringHadDot( string name ) ;
bool OnlyIDulNum( string name ) ;
void SaveTempString( string &inputTemp, int numOfLine, int numOfColum ) ;
// ------------------------------------------------------------------
bool UserInput( int &checkIndex, bool &realQuit ) ;
bool Definition( int &checkIndex, bool &realQuit ) ;
bool TypeSpecifier( int &checkIndex, bool &realQuit ) ;
bool FunctionDefinitionOrDeclarators( int &checkIndex, bool &realQuit ) ;
bool RestOfDeclarators( int &checkIndex, bool &realQuit ) ;
bool FunctionDefinitionWithoutID( int &checkIndex, bool &realQuit ) ;
bool FormalParameterList( int &checkIndex, bool &realQuit ) ;
bool CompoundStaement( int &checkIndex, bool &realQuit ) ;
bool Declaration( int &checkIndex, bool &realQuit ) ;
bool Statement( int &checkIndex, bool &realQuit ) ;
bool Expression( int &checkIndex, bool &realQuit ) ;
bool BasicExpression( int &checkIndex, bool &realQuit ) ;
bool RestOfIdentifierStartedBasicExp( int &checkIndex, bool &realQuit ) ;
bool RestOfPPMMIdentifierStartedBasicExp( int &checkIndex, bool &realQuit ) ;
bool Sign( int &checkIndex, bool &realQuit ) ;
bool ActualParameterList( int &checkIndex, bool &realQuit ) ;
bool AssignmentOperator( int &checkIndex, bool &realQuit ) ;
bool RomceAndRomloe( int &checkIndex, bool &realQuit ) ;
bool RestOfMaybeLogicalOrExp( int &checkIndex, bool &realQuit ) ;
bool MaybeLogicalAndExp( int &checkIndex, bool &realQuit ) ;
bool RestOfMaybeLogicalAndExp( int &checkIndex, bool &realQuit ) ;
bool MaybeBitOrExp( int &checkIndex, bool &realQuit ) ;
bool RestOfMaybeBitOrExp( int &checkIndex, bool &realQuit ) ;
bool MaybeBitExOrExp( int &checkIndex, bool &realQuit ) ;
bool RestOfMaybeBitExOrExp( int &checkIndex, bool &realQuit ) ;
bool MaybeBitAndExp( int &checkIndex, bool &realQuit ) ;
bool RestOfMaybeBitAndExp( int &checkIndex, bool &realQuit ) ;
bool MaybeEqualityExp( int &checkIndex, bool &realQuit ) ;
bool RestOfMaybeEqualityExp( int &checkIndex, bool &realQuit ) ;
bool MaybeRelationalExp( int &checkIndex, bool &realQuit ) ;
bool RestOfMaybeRelationalExp( int &checkIndex, bool &realQuit ) ;
bool MaybeShiftExp( int &checkIndex, bool &realQuit ) ;
bool RestOfMaybeShiftExp( int &checkIndex, bool &realQuit ) ;
bool MaybeAdditiveExp( int &checkIndex, bool &realQuit ) ;
bool RestOfMaybeAdditiveExp( int &checkIndex, bool &realQuit ) ;
bool MaybeMultExp( int &checkIndex, bool &realQuit ) ;
bool RestOfMaybeMultExp( int &checkIndex, bool &realQuit ) ;
bool UnaryExp( int &checkIndex, bool &realQuit ) ;
bool SignedUnaryExp( int &checkIndex, bool &realQuit ) ;
bool UnsignedUnaryExp( int &checkIndex, bool &realQuit ) ;

bool DoDefinition( int &checkIndex ) ;
bool DoTypeSpecifier( int &checkIndex, string &whichType ) ;
bool DoFunctionDefinitionOrDeclarators( int &checkIndex, bool &isFunction ) ;

bool DoRestOfDeclarators( int &checkIndex ) ;
bool DoAgainRestOfDeclarators( int &head, bool IDExistList, int IndexInIDList,
                               string tmepIDName, string whichType ) ;

bool DoFunctionDefinitionWithoutID( int &checkIndex ) ;
bool DoFormalParameterList( int &checkIndex ) ;
bool DoCompoundStaement( int &checkIndex ) ;
bool DoDeclaration( int &checkIndex ) ;
bool DoStatement( int &checkIndex ) ;
bool DoExpression( int &checkIndex ) ;
bool DoBasicExpression( int &checkIndex ) ;
bool DoRestOfIdentifierStartedBasicExp( int &checkIndex ) ;
bool DoRestOfPPMMIdentifierStartedBasicExp( int &checkIndex ) ;
bool DoSign( int &checkIndex ) ;
bool DoActualParameterList( int &checkIndex ) ;
bool DoAssignmentOperator( int &checkIndex ) ;
bool DoRomceAndRomloe( int &checkIndex ) ;
bool DoRestOfMaybeLogicalOrExp( int &checkIndex ) ;
bool DoMaybeLogicalAndExp( int &checkIndex ) ;
bool DoRestOfMaybeLogicalAndExp( int &checkIndex ) ;
bool DoMaybeBitOrExp( int &checkIndex ) ;
bool DoRestOfMaybeBitOrExp( int &checkIndex ) ;
bool DoMaybeBitExOrExp( int &checkIndex ) ;
bool DoRestOfMaybeBitExOrExp( int &checkIndex ) ;
bool DoMaybeBitAndExp( int &checkIndex ) ;
bool DoRestOfMaybeBitAndExp( int &checkIndex ) ;
bool DoMaybeEqualityExp( int &checkIndex ) ;
bool DoRestOfMaybeEqualityExp( int &checkIndex ) ;
bool DoMaybeRelationalExp( int &checkIndex ) ;
bool DoRestOfMaybeRelationalExp( int &checkIndex ) ;
bool DoMaybeShiftExp( int &checkIndex ) ;
bool DoRestOfMaybeShiftExp( int &checkIndex ) ;
bool DoMaybeAdditiveExp( int &checkIndex ) ;
bool DoRestOfMaybeAdditiveExp( int &checkIndex ) ;
bool DoMaybeMultExp( int &checkIndex ) ;
bool DoRestOfMaybeMultExp( int &checkIndex ) ;
bool DoUnaryExp( int &checkIndex ) ;
bool DoSignedUnaryExp( int &checkIndex ) ;
bool DoUnsignedUnaryExp( int &checkIndex ) ;
// ------------------------------------------------------------------

void SaveTempString( string &inputTemp, int numOfLine, int numOfColum ) {
  TokenData tempToken ; 
  tempToken.name = inputTemp ;
  tempToken.whereLine = numOfLine ;
  tempToken.whereColum = numOfColum - inputTemp.size() ;
  if ( IsStringOnlyNumDot( inputTemp ) == true ) {
    tempToken.type = "Constant" ;
    if ( IsStringHadDot( inputTemp ) == true ) 
      tempToken.constantType = "float" ;
    else 
      tempToken.constantType = "int" ;
  } // if 
  else if ( inputTemp[0] == '\'' || inputTemp[0] == '\"' ) {
    tempToken.type = "Constant" ;
    // printf("YES") ;
    if ( inputTemp[0] == '\'' ) 
      tempToken.constantType = "single" ;
    else 
      tempToken.constantType = "double" ;
  } // else if
  else if ( inputTemp == "true" || inputTemp == "false" ) {
    tempToken.type = "Constant" ;
    if ( inputTemp == "true" ) 
      tempToken.constantType = "true" ;
    else 
      tempToken.constantType = "false" ;
  } // else if
  else if ( inputTemp == "int" || inputTemp == "float" || inputTemp == "char" || inputTemp == "bool" ||
            inputTemp == "string" || inputTemp == "void" || inputTemp == "if" || inputTemp == "else" || 
            inputTemp == "while" || inputTemp == "do" || inputTemp == "return" ) 
    tempToken.type = inputTemp ;
  else if ( inputTemp == ">=" ) 
    tempToken.type = "ge" ;
  else if ( inputTemp == "<=" ) 
    tempToken.type = "le" ;
  else if ( inputTemp == "==" ) 
    tempToken.type = "eq" ;
  else if ( inputTemp == "!=" ) 
    tempToken.type = "neq" ;
  else if ( inputTemp == "&&" ) 
    tempToken.type = "and" ;
  else if ( inputTemp == "||" ) 
    tempToken.type = "or" ;
  else if ( inputTemp == "+=" ) 
    tempToken.type = "pe" ;
  else if ( inputTemp == "-=" ) 
    tempToken.type = "me" ;
  else if ( inputTemp == "*=" ) 
    tempToken.type = "te" ;
  else if ( inputTemp == "/=" ) 
    tempToken.type = "de" ;
  else if ( inputTemp == "%=" ) 
    tempToken.type = "re" ;
  else if ( inputTemp == "++" ) 
    tempToken.type = "pp" ;
  else if ( inputTemp == "--" ) 
    tempToken.type = "mm" ;
  else if ( inputTemp == ">>" ) 
    tempToken.type = "rs" ;
  else if ( inputTemp == "<<" ) 
    tempToken.type = "ls" ;
  else if ( inputTemp == "(" || inputTemp == ")" || inputTemp == "[" || inputTemp == "]" ||
            inputTemp == "{" || inputTemp == "}" || inputTemp == "+" || inputTemp == "-" || 
            inputTemp == "*" || inputTemp == "/" || inputTemp == ">" || inputTemp == "<" || 
            inputTemp == "^" || inputTemp == "%" || inputTemp == "&" || inputTemp == "|" || 
            inputTemp == "=" || inputTemp == "!" || inputTemp == "?" || inputTemp == ":" ||
            inputTemp == ";" || inputTemp == "," ) 
    tempToken.type = "symble" ;
  else if ( OnlyIDulNum( inputTemp ) ) 
    tempToken.type = "identifier" ;
  
  inputTemp.clear() ;
  gInput.push_back( tempToken ) ;
} // SaveTempString()

void PrintInput() {
  for ( int num = 0 ; num < gInput.size() ; num ++ ) {
    if ( num > 0 ) {
      int numofLine = gInput[num].whereLine - gInput[num-1].whereLine ;
      for ( int numofLine = gInput[num].whereLine - gInput[num-1].whereLine ; numofLine > 0 ; numofLine-- )
        printf( "\n" ) ;
    } // if

    printf( "%s*%d %d   ", gInput[num].name.c_str(), gInput[num].whereLine, gInput[num].whereColum ) ;
  } // for
  
} // PrintInput()

bool IsStringOnlyNumDot( string name ) {
  int num = 0 ;
  for ( int i = 0 ; i < name.length() ; i++ ) {
    if ( ( name[i] >= 48 && name[i] <= 57 ) || name[i] == 46 )
      num = num + 0 ;
    else 
      num++ ;
  } // for
  
  if ( num > 0 )
    return false ;
  else 
    return true ;
  
} // IsStringOnlyNumDot()

bool IsStringHadDot( string name ) {
  int num = 0 ;
  for ( int i = 0 ; i < name.length() ; i++ ) {
    if ( name[i] == 46 )
      num++ ;
  } // for
  
  if ( num > 0 )
    return true ;
  else 
    return false ;
} // IsStringHadDot()

bool OnlyIDulNum( string name ) {
  int ans = 0 ;
  for ( int i = 0 ; i < name.length() ; i++ ) {
    if ( ( name[i] >= 48 && name[i] <= 57 ) || // num
         ( name[i] >= 65 && name[i] <= 90 ) || // A-Z
         ( name[i] >= 97 && name[i] <= 122 ) || // a-z
         name[i] == '_' ) { 
      ans = ans ;
    } // if
    else
      ans++ ;
  } // for()
    
  if ( ans > 0 )
    return false ;
  else 
    return true ;
} // OnlyIDulNum()

void Scaner( char &uTestNum ) {
  char ch = '\0';
  string inputTemp ;
  int numOfLine = 1 ;
  int numOfColum = 1 ;
  uTestNum = scanf( "%c", &ch ) ;
  inputTemp = inputTemp + ch ;
  SaveTempString( inputTemp, numOfLine, numOfColum ) ;
  
  while ( scanf( "%c", &ch ) == true ) { // scanf( "%c", &ch ) == true
    if ( ch == ' '  || ch == '\t' || ch == '\n' ) {
      if ( !inputTemp.empty() )
        SaveTempString( inputTemp, numOfLine, numOfColum ) ; 
      
      if ( ch == '\n' ) { 
        numOfColum = 1 ;
        numOfLine++ ;
      } // if
      else 
        numOfColum++ ;
      
    } // if()
    /*
    else if ( inputTemp == "int" || inputTemp == "float" || inputTemp == "char" || inputTemp == "bool" ||
              inputTemp == "string" || inputTemp == "void" || inputTemp == "if" || inputTemp == "else" || 
              inputTemp == "while" || inputTemp == "do" || inputTemp == "return"  // identifier
            ) {
      SaveTempString( inputTemp, numOfLine, numOfColum ) ; 
      inputTemp = inputTemp + ch ;
      numOfColum ++ ;
    } // else if 
    else if ( inputTemp == "true" || inputTemp == "false" ) {
      SaveTempString( inputTemp, numOfLine, numOfColum ) ; 
      inputTemp = inputTemp + ch ;
      numOfColum ++ ;
    } // else if 
    */
    else if ( ch <= 57 && ch >= 48 ) { // num
      if ( OnlyIDulNum( inputTemp ) == true || IsStringOnlyNumDot( inputTemp ) == true ) {
        inputTemp = inputTemp + ch ;
        numOfColum ++ ;
      } // if
      else { // IsStringOnlyNumDot( inputTemp ) == false ) {
        if ( !inputTemp.empty() )
          SaveTempString( inputTemp, numOfLine, numOfColum ) ; 
        
        inputTemp = inputTemp + ch ;
        numOfColum ++ ;
      } // else 
    } // else if 
    else if ( ch == '.' ) { // dot
      if ( IsStringOnlyNumDot( inputTemp ) == false || IsStringHadDot( inputTemp ) == true ) 
        SaveTempString( inputTemp, numOfLine, numOfColum ) ; 
        
      inputTemp = inputTemp + ch ;
      numOfColum ++ ;
    } // else if 
    else if ( ch == '\'' ) { // '
      if ( inputTemp == "'" ) {
        inputTemp = inputTemp + ch ;
        numOfColum ++ ;
        SaveTempString( inputTemp, numOfLine, numOfColum ) ; 
      } // if 
      else {
        if ( !inputTemp.empty() ) 
          SaveTempString( inputTemp, numOfLine, numOfColum ) ; 
        
        inputTemp = inputTemp + ch ;
        numOfColum ++ ;
        // scanf( "%c", &ch ) ;
        // inputTemp = inputTemp + ch ;
        while ( scanf( "%c", &ch ) == true && ch != '\'' )  {
          inputTemp = inputTemp + ch ;
          if ( ch != '\n' )
            numOfColum ++ ;
          else {
            numOfColum = 1 ;
            numOfLine++ ;
          } // else
            
          // scanf( "%c", &ch ) ;
        } // while
        
        inputTemp = inputTemp + ch ;
        numOfColum ++ ;
        // printf("%s",inputTemp.c_str()) ;
        SaveTempString( inputTemp, numOfLine, numOfColum ) ;  // ' ' done
        // printf("%s",inputTemp.c_str()) ;
        /*
        scanf( "%c", &ch ) ;
        while ( scanf( "%c", &ch ) == true && ( ch == ' ' || ch == '\n' || ch == '\t' ) ) {
          if ( ch != '\n' )
            numOfColum ++ ;
          else {
            numOfColum = 1 ;
            numOfLine++ ;
          } // else
          
          // scanf( "%c", &ch ) ;
        } // while
        
        inputTemp = inputTemp + ch ;
        numOfColum ++ ;
        */
      } // else 
    } // else if 
    else if ( ch == '"' ) { // "
      if ( inputTemp == "\"" ) {
        inputTemp = inputTemp + ch ;
        numOfColum ++ ;
        SaveTempString( inputTemp, numOfLine, numOfColum ) ; 
      } // if 
      else {
        if ( !inputTemp.empty() ) 
          SaveTempString( inputTemp, numOfLine, numOfColum ) ; 
        
        inputTemp = inputTemp + ch ;
        numOfColum ++ ;
        // scanf( "%c", &ch ) ;
        // inputTemp = inputTemp + ch ;
        while ( scanf( "%c", &ch ) == true && ch != '\"' )  {
          // printf("%c", ch) ;
          inputTemp = inputTemp + ch ;
          if ( ch != '\n' )
            numOfColum ++ ;
          else {
            numOfColum = 1 ;
            numOfLine++ ;
          } // else
            
          // scanf( "%c", &ch ) ;
        } // while
        
        // printf("*%s*",inputTemp.c_str() ) ;
        
        inputTemp = inputTemp + ch ;
        numOfColum ++ ;
        // printf("%s",inputTemp.c_str()) ;
        SaveTempString( inputTemp, numOfLine, numOfColum ) ;  // "" done
        /*
        scanf( "%c", &ch ) ;
        while ( scanf( "%c", &ch ) == true && ( ch == ' ' || ch == '\n' || ch == '\t' ) ) {
          if ( ch != '\n' )
            numOfColum ++ ;
          else {
            numOfColum = 1 ;
            numOfLine++ ;
          } // else
          
          // scanf( "%c", &ch ) ;
        } // while
        
        inputTemp = inputTemp + ch ;
        numOfColum ++ ;
        */
      } // else 
    } // else if 
    else if ( ch == '(' || ch == ')' || ch == '[' || ch == ']' || ch == '{' || ch == '}' ||
              ch == '^' || ch == ';' || ch == ',' || ch == '?' || ch == ':' ) { 
      if ( !inputTemp.empty() )
        SaveTempString( inputTemp, numOfLine, numOfColum ) ; 
      
      inputTemp = inputTemp + ch ;
      numOfColum ++ ;
      SaveTempString( inputTemp, numOfLine, numOfColum ) ; 
    } // else if 
    else if ( ch == '=' ) {
      if ( inputTemp == ">" || inputTemp == "<" || inputTemp == "+" || inputTemp == "-" ||
           inputTemp == "*" || inputTemp == "/" || inputTemp == "%" || inputTemp == "!" || 
           inputTemp == "=" ) {
        inputTemp = inputTemp + ch ;
        numOfColum ++ ;
        SaveTempString( inputTemp, numOfLine, numOfColum ) ; 
      } // if 
      else {
        if ( !inputTemp.empty() )
          SaveTempString( inputTemp, numOfLine, numOfColum ) ; 
        
        inputTemp = inputTemp + ch ;
        numOfColum ++ ;
      } // else 
    } // else if 
    else if ( ch == '/' ) { 
      if ( inputTemp == "/" ) {
        inputTemp.clear() ;
        scanf( "%c", &ch ) ;
        while ( scanf( "%c", &ch ) == true && ch != '\n' ) {
          int a = 0 ;
        } // while 
          
        numOfColum = 1; 
        numOfLine++ ;        
      } // if
      else {
        if ( !inputTemp.empty() )
          SaveTempString( inputTemp, numOfLine, numOfColum ) ; 

        inputTemp = inputTemp + ch ;
        numOfColum++ ;
      } // else
        
    } // else if()
    else if ( ch == '*' || ch == '%' || ch == '!' ) {
      if ( !inputTemp.empty() )
        SaveTempString( inputTemp, numOfLine, numOfColum ) ; 
      
      inputTemp = inputTemp + ch ;
      numOfColum ++ ;
    } // else if
    else if ( ch == '+' || ch == '-' || ch == '>' || ch == '<' ) {
      if ( ch == '+' && inputTemp == "+" ) {
        inputTemp = inputTemp + ch ;
        numOfColum ++ ;
        SaveTempString( inputTemp, numOfLine, numOfColum ) ; 
      } // if 
      else if ( ch == '-' && inputTemp == "-" ) {
        inputTemp = inputTemp + ch ;
        numOfColum ++ ;
        SaveTempString( inputTemp, numOfLine, numOfColum ) ; 
      } // else if  
      else if ( ch == '>' && inputTemp == ">" ) {
        inputTemp = inputTemp + ch ;
        numOfColum ++ ;
        SaveTempString( inputTemp, numOfLine, numOfColum ) ; 
      } // else if  
      else if ( ch == '<' && inputTemp == "<" ) {
        inputTemp = inputTemp + ch ;
        numOfColum ++ ;
        SaveTempString( inputTemp, numOfLine, numOfColum ) ; 
      } // else if  
      else {
        if ( !inputTemp.empty() )
          SaveTempString( inputTemp, numOfLine, numOfColum ) ; 
        
        inputTemp = inputTemp + ch ;
        numOfColum ++ ;
      } // else 
    } // else if
    else if ( ch == '&' || ch == '|' ) {
      if ( ch == '&' && inputTemp == "&" ) {
        inputTemp = inputTemp + ch ;
        numOfColum ++ ;
        SaveTempString( inputTemp, numOfLine, numOfColum ) ; 
      } // if 
      else if ( ch == '|' && inputTemp == "|" ) {
        inputTemp = inputTemp + ch ;
        numOfColum ++ ;
        SaveTempString( inputTemp, numOfLine, numOfColum ) ; 
      } // else if  
      else { // only & or |
        if ( !inputTemp.empty() )
          SaveTempString( inputTemp, numOfLine, numOfColum ) ; 
        
        inputTemp = inputTemp + ch ;
        numOfColum ++ ;
      } // else 
    } // else if 
    else if ( ch == '_' ||
              ( ch >= 65 && ch <= 90 ) || ( ch >= 97 && ch <= 122 ) ) { // A-Z a-z 
      if ( IsStringOnlyNumDot( inputTemp ) == true ) {
        if ( !inputTemp.empty() )
          SaveTempString( inputTemp, numOfLine, numOfColum ) ; 
        inputTemp = inputTemp + ch ;
        numOfColum ++ ;
      } // if
      else if ( OnlyIDulNum( inputTemp ) == true ) {
        inputTemp = inputTemp + ch ;
        numOfColum ++ ;
      } // else if
      else {
        if ( !inputTemp.empty() )
          SaveTempString( inputTemp, numOfLine, numOfColum ) ; 
        inputTemp = inputTemp + ch ;
        numOfColum ++ ;
      } // else 
    } // else if 
    else if ( ch == '#' || ch == '@' || ch == '$' ) {
      if ( !inputTemp.empty() )
        SaveTempString( inputTemp, numOfLine, numOfColum ) ; 
      inputTemp = inputTemp + ch ;
      numOfColum ++ ;
    } // else if
    else {
      inputTemp = inputTemp + ch ;
      numOfColum ++ ;
      // printf( "MAY BE GET TOKEN ERROR" ) ;
    } // else
    
  } // while ()
    
  if ( !inputTemp.empty() )  
    SaveTempString( inputTemp, numOfLine, numOfColum ) ;

} // Scaner()

// ------------------------------------------------------------------

bool UnrecognizeToken( string name ) {
  int num = 0 ;
  for ( int i = 0 ; i < name.length() ; i++ )
    if ( name[i] == '@' || name[i] == '#' || name[i] == '$' ) 
      num ++ ;
  
  if ( num > 0 ) 
    return true ;
  else 
    return false ;
  
} // UnrecognizeToken()

void UnexpectedThrow( int &checkIndex ) { // , int lineNum
  if ( UnrecognizeToken( gInput[checkIndex].name ) == true ) { 
    if ( gInput[checkIndex].name.length() > 1 )
      gInput[checkIndex].name.erase( 1 ) ;
    
    int line = gInput[checkIndex].whereLine - gInput[gInputHead].whereLine ;
    if ( line == 0 ) 
      line = 1 ;
    printf( "> Line %d : ", line ) ; 
    string error = "unrecognized token with first char : '" + gInput[checkIndex].name ;
    throw error ;
  } // if 
  
  int line = gInput[checkIndex].whereLine - gInput[gInputHead].whereLine ;
  if ( line == 0 ) 
    line = 1 ;
  printf( "> Line %d : ", line ) ;
  string ans = "unexpected token : '" + gInput[checkIndex].name ;
  throw ans ;
} // UnexpectedThrow()

void UndefinedThrow( int &checkIndex ) { // , int lineNum
  // printf( "%d%s%d %d%s%d", checkIndex,gInput[checkIndex].name,
  // gInput[checkIndex].whereLine,gInputHead,gInput[gInputHead].name.c_str(),gInput[gInputHead].whereLine ) ;
  // printf( "UndefinedThrow%d*", checkIndex ) ;
  int line = gInput[checkIndex].whereLine - gInput[gInputHead].whereLine ;
  if ( line == 0 ) 
    line = 1 ;
  printf( "> Line %d : ", line ) ;
  string ans = "undefined identifier : '" + gInput[checkIndex].name ;
  // printf( "*%d*", checkIndex ) ;
  // checkIndex++ ;
  throw ans ;
} // UndefinedThrow()

void CheckUnrecognizeToken( string name, int &checkIndex ) { // , int lineNum
  if ( UnrecognizeToken( name ) == true ) { 
    if ( name.length() > 1 )
      name.erase( 1 ) ;
    
    int line = gInput[checkIndex].whereLine - gInput[gInputHead].whereLine ;
    if ( line == 0 ) 
      line = 1 ;
    printf( "> Line %d : ", line ) ; 
    string error = "unrecognized token with first char : '" + name ;
    throw error ;
  } // if 
} // CheckUnrecognizeToken()

void ListAllVariables() {
  // printf("ListAllVariables") ;
  vector<IDENTData> idListTemp ;
  IDENTData temp ;
  for ( int i = 0 ; i < gIDList.size() ; i ++ ) {
    temp.name = gIDList[i].name ;
    idListTemp.push_back( temp ) ;
  } // for 
  
  for ( int i = 0 ; i < idListTemp.size() ; i ++ ) {
    for ( int j = 0 ; j < i ; j ++ ) {
      if ( idListTemp[j].name > idListTemp[i].name ) {
        // swap( idListTemp[j], idListTemp[i] ) ;
        IDENTData temp1 ;
        IDENTData temp2 ;
        temp1.name = idListTemp[i].name ;
        temp2.name = idListTemp[j].name ;
        idListTemp.erase( idListTemp.begin() + i ) ;
        idListTemp.erase( idListTemp.begin() + j ) ;
        idListTemp.insert( idListTemp.begin() + j, temp2 ) ;
        idListTemp.insert( idListTemp.begin() + j, temp1 ) ;
      } // if 
    } // for
  } // for
  
  printf( "> " ) ;
  for ( int i = 0 ; i < idListTemp.size() ; i++ ) {
    printf( "%s\n", idListTemp[i].name.c_str() ) ;
  } // for
  
  printf( "Statement executed ...\n" ) ;
} // ListAllVariables()

void ListAllFunctions() {
  // printf("ListAllFunctions") ;
  vector<FunctionInfo> funrtionTemp ;
  FunctionInfo temp ;
  for ( int i = 0 ; i < gFunction.size() ; i ++ ) {
    temp.functionName = gFunction[i].functionName ;
    funrtionTemp.push_back( temp ) ;
  } // for 
  
  for ( int i = 0 ; i < funrtionTemp.size() ; i ++ ) {
    for ( int j = 0 ; j < i ; j ++ ) {
      if ( funrtionTemp[j].functionName > funrtionTemp[i].functionName ) {
        // swap( funrtionTemp[j], funrtionTemp[i] );
        FunctionInfo temp1 ;
        FunctionInfo temp2 ;
        temp1.functionName = funrtionTemp[i].functionName ;
        temp2.functionName = funrtionTemp[j].functionName ;
        funrtionTemp.erase( funrtionTemp.begin() + i ) ; // may error here
        funrtionTemp.erase( funrtionTemp.begin() + j ) ;
        funrtionTemp.insert( funrtionTemp.begin() + j, temp2 ) ;
        funrtionTemp.insert( funrtionTemp.begin() + j, temp1 ) ;
      } // if 
    } // for
  } // for
  
  printf( "> " ) ;
  for ( int i = 0 ; i < funrtionTemp.size() ; i++ ) 
    printf( "%s()\n", funrtionTemp[i].functionName.c_str() ) ;
  
  printf( "Statement executed ...\n" ) ;
  
} // ListAllFunctions()

void ListFunction( string name, int &checkIndex ) { // Indent
  string ans = "" ;
  if ( name == "\"\"" || name == "''" ) {
    int line = gInput[checkIndex].whereLine - gInput[gInputHead].whereLine ;
    if ( line == 0 ) 
      line = 1 ;
    
    printf( "> Line %d : ", line ) ;
    if ( name == "\"\"" )
      ans = "unexpected token : '\""  ;
    else 
      ans = "unexpected token : ''"  ;
    throw ans ;
  } // if 
  // printf("ListFunction") ;
  int space = 0 ;
  name.erase( name.end() - 1 );
  name.erase( 0, 1 ) ;
  // printf("**%s**", name.c_str() ) ;
  
  printf( "> " ) ;
  for ( int i = 0 ; i < gFunction.size() ; i++ ) {
    if ( gFunction[i].functionName == name ) {
      for ( int j = 0 ; j < gFunction[i].functionToken.size() ; j++ ) {
        if ( gFunction[i].functionToken[j].name == "{" || gFunction[i].functionToken[j].name == "}" ) {
          if ( gFunction[i].functionToken[j].name == "{" ) 
            space = space + 2 ;
          else if ( gFunction[i].functionToken[j].name == "}" ) 
            space = space - 2 ;
        } // if 
        
        if ( gFunction[i].functionToken[j].type == "identifier" &&
             gFunction[i].functionToken[j+1].name == "(" ) {
          if ( j > 0 && 
               ( gFunction[i].functionToken[j-1].name == "{" ||
                 gFunction[i].functionToken[j-1].name == ";" || 
                 gFunction[i].functionToken[j-1].name == "}" ) ) {
            printf( "\n" ) ;
            for ( int x = 0 ; x < space - 1 ; x ++ )
              printf( " " ) ;
          } // if
          
          printf( " %s(", gFunction[i].functionToken[j].name.c_str() ) ; 
          j++ ;
        } // if
        else if ( gFunction[i].functionToken[j].type == "identifier" &&
                  gFunction[i].functionToken[j+1].name == "[" ) {
          if ( j > 0 && 
               ( gFunction[i].functionToken[j-1].name == "{" ||
                 gFunction[i].functionToken[j-1].name == ";" || 
                 gFunction[i].functionToken[j-1].name == "}" ) ) {
            printf( "\n" ) ;
            for ( int x = 0 ; x < space - 1 ; x ++ )
              printf( " " ) ;
          } // if
          
          printf( " %s[", gFunction[i].functionToken[j].name.c_str() ) ; 
          j++ ;
        } // else if
        else if ( gFunction[i].functionToken[j].type == "identifier" &&
                  gFunction[i].functionToken[j+1].name == "--" ) {
          if ( j > 0 && 
               ( gFunction[i].functionToken[j-1].name == "{" ||
                 gFunction[i].functionToken[j-1].name == ";" || 
                 gFunction[i].functionToken[j-1].name == "}" ) ) {
            printf( "\n" ) ;
            for ( int x = 0 ; x < space - 1 ; x ++ )
              printf( " " ) ;
          } // if
          
          printf( " %s--", gFunction[i].functionToken[j].name.c_str() ) ; 
          j++ ;
        } // else if
        else if ( gFunction[i].functionToken[j].type == "identifier" &&
                  gFunction[i].functionToken[j+1].name == "++" ) {
          if ( j > 0 && 
               ( gFunction[i].functionToken[j-1].name == "{" ||
                 gFunction[i].functionToken[j-1].name == ";" || 
                 gFunction[i].functionToken[j-1].name == "}" ) ) {
            printf( "\n" ) ;
            for ( int x = 0 ; x < space - 1 ; x ++ )
              printf( " " ) ;
          } // if
          
          printf( " %s++", gFunction[i].functionToken[j].name.c_str() ) ; 
          j++ ;
        } // else if
        else if ( j == 0 ) {
          printf( "%s", gFunction[i].functionToken[j].name.c_str() ) ; 
        } // else if 
        else {
          if ( gFunction[i].functionToken[j-1].name == "{" || gFunction[i].functionToken[j-1].name == ";" ) {
            printf( "\n" ) ;
            for ( int x = 0 ; x < space ; x ++ )
              printf( " " ) ;
            printf( "%s", gFunction[i].functionToken[j].name.c_str() ) ;
          } // if 
          else if ( gFunction[i].functionToken[j-1].name == "}" ) {
            printf( "\n" ) ;
            for ( int x = 0 ; x < space ; x ++ )
              printf( " " ) ;
            printf( "%s", gFunction[i].functionToken[j].name.c_str() ) ;
          } // else if 
          else if ( gFunction[i].functionToken[j].name == "," ) {
            printf( "%s", gFunction[i].functionToken[j].name.c_str() ) ; 
          } // else if 
          else 
            printf( " %s", gFunction[i].functionToken[j].name.c_str() ) ; 
        } // else
      } // for
    } // if 
  } // for
  
  printf( "\nStatement executed ...\n" ) ;

} // ListFunction()

void ListVariable( string name, int &checkIndex ) {
  string ans = "" ;
  if ( name == "\"\"" || name == "''" ) {
    int line = gInput[checkIndex].whereLine - gInput[gInputHead].whereLine ;
    if ( line == 0 ) 
      line = 1 ;
    
    printf( "> Line %d : ", line ) ;
    // printf("??%s??", gInput[gInputHead-3].name.c_str()) ;
    if ( name == "\"\"" )
      ans = "unexpected token : '\""  ;
    else 
      ans = "unexpected token : ''"  ;
    throw ans ;
  } // if 
  // printf("ListVariable") ;
  // printf("%s", name.c_str()) ;
  name.erase( name.end() - 1 );
  name.erase( 0, 1 );
  printf( "> " ) ;
  // printf("%d", gIDList.size()) ;
  // printf("%s", name.c_str()) ;
  for ( int i = 0 ; i < gIDList.size() ; i++ ) {
    if ( gIDList[i].name == name ) {
      printf( "%s %s", gIDList[i].type.c_str(), gIDList[i].name.c_str() ) ;  
      if ( gIDList[i].constant.length() > 0 ) 
        printf( "[ %s ]", gIDList[i].constant.c_str() ) ;  
      
      printf( " ;\n" ) ;  
    } // if 
  } // for
  
  printf( "Statement executed ...\n" ) ;
} // ListVariable()

bool IDExist( string name, int &where ) {
  if ( name == "cout" || name == "cin" )
    return true ;
  
  where = -1 ;
  for ( int i = 0 ; i < gIDList.size() ; i++ ) {
    if ( gIDList[i].name == name )
      where = i ;
  } // for
  
  if ( where == -1 )
    return false ;
  else 
    return true ;
  
} // IDExist()

bool IDExistTemp( string name, int &where ) {
  if ( name == "cout" || name == "cin" )
    return true ;
  
  where = -1 ;
  for ( int i = 0 ; i < gIDTemp.size() ; i++ ) {
    if ( gIDTemp[i].name == name )
      where = i ;
  } // for
  
  if ( where == -1 )
    return false ;
  else 
    return true ;
} // IDExistTemp()

bool FunctionExist( string name, int &where ) {
  if ( name == "ListAllVariables" || name == "ListAllFunctions" || name == "ListVariable" ||
       name == "ListFunction" || name == "Done" )
    return true ;
  
  where = -1 ;
  for ( int i = 0 ; i < gFunction.size() ; i++ ) {
    if ( gFunction[i].functionName == name )
      where = i ;
  } // for
  
  if ( where == -1 )
    return false ;
  else 
    return true ;
} // FunctionExist()

void DeleteIDTemp( int num ) { 
  if ( num == 0 ) {
    int a = 0 ;
  } // if 
  else {
    bool breakwhile = false ;
    while ( num > 0 && breakwhile == false ) {
      if ( gIDTemp.size() == 0 ) {
        breakwhile = true ;
      } // if 

      gIDTemp.pop_back() ;
      num -- ;

    } // while()
      
  } // else 
    
} // DeleteIDTemp()

bool CheckSepcial( int &checkIndex, bool &realQuit ) {
  if ( checkIndex + 3 < gInput.size() &&
       ( gInput[checkIndex].name == "Done" && gInput[checkIndex+1].name == "(" &&
         gInput[checkIndex+2].name == ")" && gInput[checkIndex+3].name == ";" ) == true ) {
    checkIndex = checkIndex + 4 ;
    gInputHead = checkIndex - 1 ;
    // printf("HEHE") ;
    realQuit = true ;
    return true ;
  } // if 
  else if ( gInput[checkIndex].name == "ListAllVariables" && checkIndex + 3 < gInput.size() &&
            gInput[checkIndex+1].name == "(" && gInput[checkIndex+2].name == ")" &&
            gInput[checkIndex+3].name == ";" ) {
    ListAllVariables() ;
    checkIndex = checkIndex + 4 ;
    gInputHead = checkIndex - 1 ;
    return true ;
  } // else if 
  else if ( gInput[checkIndex].name == "ListAllFunctions" && checkIndex + 3 < gInput.size() &&
            gInput[checkIndex+1].name == "(" && gInput[checkIndex+2].name == ")" &&
            gInput[checkIndex+3].name == ";" ) {
    ListAllFunctions() ;
    checkIndex = checkIndex + 4 ;
    return true ;
  } // else if 
  else if ( gInput[checkIndex].name == "ListVariable" && checkIndex + 4 < gInput.size() &&
            gInput[checkIndex+1].name == "(" && gInput[checkIndex+2].type == "Constant" &&
            gInput[checkIndex+3].name == ")" && gInput[checkIndex+4].name == ";" 
          ) { // ListVariable ( Constant ) ; ListVariable ( "string" ) ;
    checkIndex = checkIndex + 2 ;
    ListVariable( gInput[checkIndex].name, checkIndex ) ;
    checkIndex = checkIndex + 3 ;
    gInputHead = checkIndex - 1 ;
    return true ;
  } // else if 
  else if ( gInput[checkIndex].name == "ListFunction" && checkIndex + 4 < gInput.size() &&
            gInput[checkIndex+1].name == "(" && gInput[checkIndex+2].type == "Constant" &&
            gInput[checkIndex+3].name == ")" && gInput[checkIndex+4].name == ";" 
          ) { // ListFunction ( Constant ) ; ListFunction ( "ADDFIVE" ) ;ListFunction( 'S' ) ;
    checkIndex = checkIndex + 2 ;
    ListFunction( gInput[checkIndex].name, checkIndex ) ;
    checkIndex = checkIndex + 3 ;
    gInputHead = checkIndex - 1 ;
    return true ;
  } // else if 
  else 
    return false ;
  
} // CheckSepcial()

void SaveFunction( int head, int tail, bool FunctionExist, int IndexInFuncList ) {
  TokenData tmepToken ;
  FunctionInfo tmepFunction ;
  
  if ( FunctionExist == true ) 
    gFunction.erase( gFunction.begin() + IndexInFuncList ) ;

  tmepFunction.functionName = gInput[head+1].name ;
  for ( int i = head ; i <= tail ; i++ ) {
    tmepToken.name = gInput[i].name ; 
    tmepToken.type = gInput[i].type ; 
    tmepToken.constantType = gInput[i].constantType ; 
    tmepToken.whereColum = gInput[i].whereColum ; 
    tmepToken.whereLine = gInput[i].whereLine ; 
    tmepFunction.functionToken.push_back( tmepToken ) ;
  } // for
  
  gFunction.push_back( tmepFunction ) ;
  /*
  for ( int i = 0 ; i < gFunction[0].functionToken.size() ; i ++ )
    printf( " %s", gFunction[0].functionToken[i].name.c_str() ) ;
  */
  
} // SaveFunction()

void PrintDefinition( int &checkIndex ) {
  if ( DoDefinition( checkIndex ) == true ) {
    int a = 0 ; 
  } // if 
  // printf( "OldPrintDef %d\n", checkIndex+1 ) ;
  // printf( "> Definition of %s entered ...\n", gInput[checkIndex+1].name.c_str() ) ;
} // PrintDefinition()

void PrintStatement( int &checkIndex, bool &realQuit ) {
  // printf( "%d %s", checkIndex, gInput[checkIndex].name ) ;
  if ( CheckSepcial( checkIndex, realQuit ) == false )
    printf( "> Statement executed ...\n" ) ;
  // printf( "%s> Statement executed ...\n",gInput[checkIndex].name ) ;
} // PrintStatement()

// ------------------------------------------------------------------

bool UserInput( int &checkIndex, bool &realQuit ) {
  CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
  int maybePrint = checkIndex ;
  if ( checkIndex == 1 )
    gInputHead = checkIndex - 1 ;
  
  // printf("%d", checkIndex) ;
  if ( gInput[checkIndex].name == "Done" && checkIndex + 3 < gInput.size() &&
       gInput[checkIndex+1].name == "(" && gInput[checkIndex+2].name == ")" &&
       gInput[checkIndex+3].name == ";" ) { // consider "Done (    ) "
    checkIndex = checkIndex + 4 ;
    gInputHead = checkIndex - 1 ;
    realQuit = true ;
    return true ;
  } // if 
  else if ( gInput[checkIndex].name == "ListAllVariables" && checkIndex + 3 < gInput.size() &&
            gInput[checkIndex+1].name == "(" && gInput[checkIndex+2].name == ")" &&
            gInput[checkIndex+3].name == ";" ) {
    ListAllVariables() ;
    checkIndex = checkIndex + 4 ;
    gInputHead = checkIndex - 1 ;
    return true ;
  } // else if 
  else if ( gInput[checkIndex].name == "ListAllFunctions" && checkIndex + 3 < gInput.size() &&
            gInput[checkIndex+1].name == "(" && gInput[checkIndex+2].name == ")" &&
            gInput[checkIndex+3].name == ";" ) {
    ListAllFunctions() ;
    checkIndex = checkIndex + 4 ;
    gInputHead = checkIndex - 1 ;
    // printf("ONE") ;
    return true ;
  } // else if 
  else if ( gInput[checkIndex].name == "ListVariable" && checkIndex + 4 < gInput.size() &&
            gInput[checkIndex+1].name == "(" && gInput[checkIndex+2].type == "Constant" &&
            gInput[checkIndex+3].name == ")" && gInput[checkIndex+4].name == ";" 
          ) { // ListVariable ( Constant ) ; ListVariable ( "string" ) ;
    checkIndex = checkIndex + 2 ;
    // printf("%d", checkIndex) ;
    ListVariable( gInput[checkIndex].name, checkIndex ) ;
    checkIndex = checkIndex + 3 ;
    gInputHead = checkIndex - 1 ;
    return true ;
  } // else if 
  else if ( gInput[checkIndex].name == "ListFunction" && checkIndex + 4 < gInput.size() &&
            gInput[checkIndex+1].name == "(" && gInput[checkIndex+2].type == "Constant" &&
            gInput[checkIndex+3].name == ")" && gInput[checkIndex+4].name == ";" 
          ) { // ListFunction ( Constant ) ; ListFunction ( "ADDFIVE" ) ;ListFunction( 'S' ) ;
    checkIndex = checkIndex + 2 ;
    ListFunction( gInput[checkIndex].name, checkIndex ) ;
    // printf("THREE") ;
    checkIndex = checkIndex + 3 ;
    gInputHead = checkIndex - 1 ;
    return true ;
  } // else if 
  else if ( checkIndex < gInput.size() && Definition( checkIndex, realQuit ) == true ) {
    // printf("UPSIDE") ;
    // printf("BB %d %s",checkIndex,  gInput[checkIndex].name);
    gIDTemp.clear() ;
    // printf("YY") ;
    // printf( "!%d!", gIDTemp.size() ) ;
    // printf( "!%s!", gIDTemp[0].name.c_str() ) ;
    // printf( "!%s!", gIDTemp[1].name.c_str() ) ;
    CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
    PrintDefinition( maybePrint ) ;
    // printf("MM") ;
    gIDTemp.clear() ;
    // printf("AA%d",checkIndex);
    maybePrint = checkIndex ;
    gInputHead = checkIndex - 1 ;
    while ( checkIndex < gInput.size() && realQuit == false &&
            ( Definition( checkIndex, realQuit ) == true || Statement( checkIndex, realQuit ) == true ) ) {
      gIDTemp.clear() ;
      // printf( "!%d!", gIDTemp.size() ) ;
      if ( gInput[maybePrint].name == "void" || gInput[maybePrint].name == "int" ||
           gInput[maybePrint].name == "float" || gInput[maybePrint].name == "bool" ||
           gInput[maybePrint].name == "char" || gInput[maybePrint].name == "string" ) {
        PrintDefinition( maybePrint ) ;
      } // if    is Definition
      else {
        PrintStatement( maybePrint, realQuit ) ;
      } // else 
      
      gIDTemp.clear() ;
      
      // printf("UPINSIDE") ;
      maybePrint = checkIndex ;
      gInputHead = checkIndex - 1 ;
      if ( checkIndex >= gInput.size() || realQuit == true )
        return true ;
      /*
      if ( checkIndex < gInput.size() )
        CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
      else 
        return true ;
      */
    } // while
  } // else if 
  else if ( checkIndex < gInput.size() && Statement( checkIndex, realQuit ) == true ) {
    // printf("DOWNSIDE") ;
    gIDTemp.clear() ;
    CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
    PrintStatement( maybePrint, realQuit ) ;
    gIDTemp.clear() ;
    maybePrint = checkIndex ;
    gInputHead = checkIndex - 1 ;
    while ( checkIndex < gInput.size() && realQuit == false &&
            ( Definition( checkIndex, realQuit ) == true || Statement( checkIndex, realQuit ) == true ) ) {
      gIDTemp.clear() ;
      if ( gInput[maybePrint].name == "void" || gInput[maybePrint].name == "int" ||
           gInput[maybePrint].name == "float" || gInput[maybePrint].name == "bool" ||
           gInput[maybePrint].name == "char" || gInput[maybePrint].name == "string" ) {
        PrintDefinition( maybePrint ) ;
      } // if    is Definition
      else 
        PrintStatement( maybePrint, realQuit ) ; 
      
      gIDTemp.clear() ;
      // printf("DownINSIDE") ;
      maybePrint = checkIndex ;
      gInputHead = checkIndex - 1 ;
      if ( checkIndex >= gInput.size() || realQuit == true )
        return true ;
    } // while 
  } // else if 
  else {
    UnexpectedThrow( checkIndex ) ;
  } // else 
    
  UnexpectedThrow( checkIndex ) ; // maybe error
  return false ;
  
} // UserInput()

bool Definition( int &checkIndex, bool &realQuit ) {
  CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
  if ( gInput[checkIndex].name == "void" ) {
    checkIndex ++ ;
    CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
    if ( gInput[checkIndex].type == "identifier" ) {
      checkIndex ++ ;
      CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
      if ( FunctionDefinitionWithoutID( checkIndex, realQuit ) == true ) {
        return true ;
      } // if 
      else {
        UnexpectedThrow( checkIndex ) ;
      } // else 
    } // if 
    else {
      UnexpectedThrow( checkIndex ) ;
    } // else 
  } // if
  else if ( TypeSpecifier( checkIndex, realQuit ) == true ) {
    CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
    if ( gInput[checkIndex].type == "identifier" ) {
      checkIndex ++ ;
      CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
      if ( FunctionDefinitionOrDeclarators( checkIndex, realQuit ) == true ) {
        return true ;
      } // if 
      else {
        UnexpectedThrow( checkIndex ) ;
      } // else 
    } // if 
    else {
      UnexpectedThrow( checkIndex ) ;
    } // else 
  } // else if 
  else {
    return false ;
  } // else 
    
  return false ;

} // Definition()

bool TypeSpecifier( int &checkIndex, bool &realQuit ) {
  CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
  if ( gInput[checkIndex].name == "int" || 
       gInput[checkIndex].name == "char" || gInput[checkIndex].name == "float" || 
       gInput[checkIndex].name == "string" || gInput[checkIndex].name == "bool" )  {
    checkIndex ++ ;
    return true ;
  } // if
  else {
    return false ;
  } // else 
    
  return false ;
  
} // TypeSpecifier()

bool FunctionDefinitionOrDeclarators( int &checkIndex, bool &realQuit ) {
  CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
  // int forFunctionDefinitionWithoutID = checkIndex ;
  // int forRestOfDeclarators = checkIndex ;
  if ( gInput[checkIndex].name == "(" ) {
    if ( FunctionDefinitionWithoutID( checkIndex, realQuit ) == true ) {
      return true ;
    } // if 
    else {
      // checkIndex = forFunctionDefinitionWithoutID ;
      return false ;
    } // else 
  } // if
  else if ( RestOfDeclarators( checkIndex, realQuit ) == true ) {
    return true ;
  } // else if 
  else {
    return false ;
  } // else 
    
} // FunctionDefinitionOrDeclarators()

bool RestOfDeclarators( int &checkIndex, bool &realQuit ) {
  CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
  if ( gInput[checkIndex].name == "[" ) {
    checkIndex ++ ;
    CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
    if ( gInput[checkIndex].type == "Constant" ) {
      checkIndex ++ ;
      CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
      if ( gInput[checkIndex].name == "]" ) {
        checkIndex ++ ;
        CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
        if ( gInput[checkIndex].name == ";" ) {
          checkIndex ++ ;
          return true ;
        } // if
        else if ( gInput[checkIndex].name == "," ) {
          while ( gInput[checkIndex].name == "," ) {
            checkIndex ++ ;
            CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
            if ( gInput[checkIndex].type == "identifier" ) {
              checkIndex ++ ;
              CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
              if ( gInput[checkIndex].name == "[" ) {
                checkIndex ++ ;
                CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
                if ( gInput[checkIndex].type == "Constant" ) {
                  checkIndex ++ ;
                  CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
                  if ( gInput[checkIndex].name == "]" ) {
                    checkIndex ++ ;
                    // CheckUnrecognizeToken( gInput[checkIndex].name ,  checkIndex ) ;
                  } // if
                  else 
                    UnexpectedThrow( checkIndex ) ;
                } // if
                else {
                  UnexpectedThrow( checkIndex ) ;
                } // else 
              } // if
              else if ( gInput[checkIndex].name == "," ) {
                int a = 0 ;
              } // else if
              else if ( gInput[checkIndex].name == ";" ) {
                checkIndex ++ ;
                return true ;
              } // else if 
              else 
                UnexpectedThrow( checkIndex ) ;
            } // if
            else 
              UnexpectedThrow( checkIndex ) ;
          } // while
          
          CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
          if ( gInput[checkIndex].name == ";" ) {
            checkIndex++ ;
            return true ; 
          } // if 
          else 
            UnexpectedThrow( checkIndex ) ;
        } // else if
        else 
          UnexpectedThrow( checkIndex ) ;
        
      } // if 
      else 
        UnexpectedThrow( checkIndex ) ;
    } // if 
    else 
      UnexpectedThrow( checkIndex ) ;
  } // if 
  else if ( gInput[checkIndex].name == "," ) {
    while ( gInput[checkIndex].name == "," ) {
      checkIndex ++ ;
      CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
      if ( gInput[checkIndex].type == "identifier" ) {
        checkIndex ++ ;
        CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
        if ( gInput[checkIndex].name == "[" ) {
          checkIndex ++ ;
          CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
          if ( gInput[checkIndex].type == "Constant" ) {
            checkIndex ++ ;
            CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
            if ( gInput[checkIndex].name == "]" ) {
              checkIndex ++ ;
              // CheckUnrecognizeToken( gInput[checkIndex].name ,  checkIndex ) ;
            } // if
            else 
              UnexpectedThrow( checkIndex ) ;
          } // if
          else 
            UnexpectedThrow( checkIndex ) ;
        } // if
        else if ( gInput[checkIndex].name == "," ) {
          int a = 0 ;
        } // else if 
        else if ( gInput[checkIndex].name == ";" ) {
          checkIndex ++ ;
          return true ;
        } // else if 
        else 
          UnexpectedThrow( checkIndex ) ;
      } // if
      else 
        UnexpectedThrow( checkIndex ) ;

    } // while
    
    CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
    if ( gInput[checkIndex].name == ";" ) {
      checkIndex ++ ;
      return true ;
    } // if
    else 
      UnexpectedThrow( checkIndex ) ;
  } // else if 
  else if ( gInput[checkIndex].name == ";" ) {
    checkIndex ++ ;
    return true ;
  } // else if 
  else {
    return false ;
  } // else 
    
  return false ;
  
} // RestOfDeclarators()

bool FunctionDefinitionWithoutID( int &checkIndex, bool &realQuit ) {
  CheckUnrecognizeToken( gInput[checkIndex].name,  checkIndex ) ;
  if ( gInput[checkIndex].name == "(" ) {
    checkIndex ++ ;
    CheckUnrecognizeToken( gInput[checkIndex].name,  checkIndex ) ;
    if ( gInput[checkIndex].name == ")" ) {
      checkIndex ++ ;
      CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
      if ( CompoundStaement( checkIndex, realQuit ) == true ) {
        return true ;
      } // if 
      else {
        UnexpectedThrow( checkIndex ) ;
      } // else 
    } // if 
    else if ( gInput[checkIndex].name == "void" ) {
      checkIndex ++ ;
      CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
      if ( gInput[checkIndex].name == ")" ) {
        checkIndex ++ ;
        CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
        if ( CompoundStaement( checkIndex, realQuit ) == true )
          return true ;
        else 
          UnexpectedThrow( checkIndex ) ;
      } // if 
      else 
        UnexpectedThrow( checkIndex ) ;
    } // else if
    else if ( FormalParameterList( checkIndex, realQuit ) == true ) {
      // checkIndex ++ ;
      CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;

      if ( gInput[checkIndex].name == ")" ) {
        checkIndex ++ ;
        CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
        if ( CompoundStaement( checkIndex, realQuit ) == true ) {
          return true ;
        } // if 
        else {
          UnexpectedThrow( checkIndex ) ;
        } // else 
      } // if 
      else 
        UnexpectedThrow( checkIndex ) ;
    } // else if
    else 
      UnexpectedThrow( checkIndex ) ;
  } // if 
  else {
    return false ;
  }  // else 
  
  return false ;
  
} // FunctionDefinitionWithoutID()

bool FormalParameterList( int &checkIndex, bool &realQuit ) {
  CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
  IDENTData temp ;
  temp.type = gInput[checkIndex].type ;
  if ( TypeSpecifier( checkIndex, realQuit ) == true ) {
    CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
    if ( gInput[checkIndex].name == "&" ) {
      checkIndex ++ ;
    } // if
    
    if ( gInput[checkIndex].type == "identifier" ) {
      temp.name = gInput[checkIndex].name ;
      gIDTemp.push_back( temp ) ;
      checkIndex ++ ;
      CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
      if ( gInput[checkIndex].name == "[" ) {
        checkIndex ++ ;
        CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
        if ( gInput[checkIndex].type == "Constant" ) {
          checkIndex ++ ;
          CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
          if ( gInput[checkIndex].name == "]" ) {
            checkIndex ++ ;
            CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
            if ( gInput[checkIndex].name == "," ) {
              while ( gInput[checkIndex].name == "," ) {
                checkIndex ++ ;
                CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
                if ( TypeSpecifier( checkIndex, realQuit ) == true ) {
                  if ( gInput[checkIndex].name == "&" ) {
                    checkIndex ++ ;
                    // CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
                  } // if 
                  
                  if ( gInput[checkIndex].type == "identifier" ) {
                    temp.name = gInput[checkIndex].name ;
                    gIDTemp.push_back( temp ) ;
                    checkIndex ++ ;
                    CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
                    if ( gInput[checkIndex].name == "[" ) {
                      checkIndex ++ ;
                      CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
                      if ( gInput[checkIndex].type == "Constant" ) {
                        checkIndex ++ ;
                        CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
                        if ( gInput[checkIndex].name == "]" ) {
                          checkIndex ++ ;
                          // CheckUnrecognizeToken( gInput[checkIndex].name ,  checkIndex ) ;
                        } // if 
                        else 
                          UnexpectedThrow( checkIndex ) ;
                      } // if 
                      else 
                        UnexpectedThrow( checkIndex ) ;
                    } // if 
                    else if ( gInput[checkIndex].name == "," ) {
                      int a = 0 ;
                    } // else if 
                    else {
                      return true ;
                    } // else 
                  } // if 
                  else 
                    UnexpectedThrow( checkIndex ) ; 
                } // if 
                else 
                  UnexpectedThrow( checkIndex ) ;
                
                // CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
              } // while 
            } // if 
            else 
              return true ;
          } // if
          else 
            UnexpectedThrow( checkIndex ) ;
        } // if 
        else 
          UnexpectedThrow( checkIndex ) ;
      } // if 
      else if ( gInput[checkIndex].name == "," ) {
        while ( gInput[checkIndex].name == "," ) {
          checkIndex ++ ;
          CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
          if ( TypeSpecifier( checkIndex, realQuit ) == true ) {
            if ( gInput[checkIndex].name == "&" ) {
              checkIndex ++ ;
              // CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
            } // if 
            
            if ( gInput[checkIndex].type == "identifier" ) {
              temp.name = gInput[checkIndex].name ;
              gIDTemp.push_back( temp ) ;
              checkIndex ++ ;
              CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
              if ( gInput[checkIndex].name == "[" ) {
                checkIndex ++ ;
                CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
                if ( gInput[checkIndex].type == "Constant" ) {
                  checkIndex ++ ;
                  CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
                  if ( gInput[checkIndex].name == "]" ) {
                    checkIndex ++ ;
                    // CheckUnrecognizeToken( gInput[checkIndex].name ,  checkIndex ) ;
                  } // if 
                  else 
                    UnexpectedThrow( checkIndex ) ;
                } // if 
                else 
                  UnexpectedThrow( checkIndex ) ;
              } // if 
              else if ( gInput[checkIndex].name == "," ) {
                int a = 0 ;
              } // else if
              else {
                return true ;
              } // else 
                
            } // if 
            else 
              UnexpectedThrow( checkIndex ) ;              
          } // if 
          else 
            UnexpectedThrow( checkIndex ) ;
          
          // CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
        } // while 
        
      } // else if 
      else 
        return true ;
        
    } // if 
    else 
      UnexpectedThrow( checkIndex ) ; // return false 
    
  } // if
  else {
    return false ;
  } // else 
  
  return false ;
  
} // FormalParameterList()

bool CompoundStaement( int &checkIndex, bool &realQuit ) {
  CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
  if ( gInput[checkIndex].name == "{" ) {
    int numIDBeforeStatement = gIDTemp.size() ;
    int numIDAfterStatement = 0 ;
    checkIndex ++ ;
    CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
    if ( gInput[checkIndex].name == "}" ) {
      checkIndex ++ ;
      return true ;
    } // if 
    else if ( Declaration( checkIndex, realQuit ) == true || Statement( checkIndex, realQuit ) == true ) {
      // numIDAfterStatement = gIDTemp.size() ;
      // DeleteIDTemp( numIDBeforeStatement - numIDAfterStatement ) ;
      // numIDBeforeStatement = gIDTemp.size() ;
      CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
      while ( Declaration( checkIndex, realQuit ) == true || Statement( checkIndex, realQuit ) == true ) {
        int a = 0 ;
        // printf("while" ) ;
        // for ( int i = 0 ; i < gIDTemp.size() ; i ++ )
          // printf("%s", gIDTemp[i].name.c_str() ) ;
        // if ( gInput[checkIndex].name == "}" ) 
          
      } // while 
      
      if ( gInput[checkIndex].name == "}" ) {
        numIDAfterStatement = gIDTemp.size() ;
        DeleteIDTemp( numIDAfterStatement - numIDBeforeStatement ) ;
        checkIndex ++ ;
        return true ;
      } // if
      else 
        UnexpectedThrow( checkIndex ) ;
      
    } // else if 
    else 
      UnexpectedThrow( checkIndex ) ;
  } // if
  else {
    return false ;
  } // else
  
  return false ;
  
} // CompoundStaement()

bool FunctionRestOfDeclarators( int &checkIndex, string tmepIDName ) { // , string whichType
  /*
  if ( IDExistList == true ) {
    gIDTemp.erase( gIDTemp.begin() + IndexInIDList ) ;
  } // if 
  */

  IDENTData tempID ;
  tempID.name = tmepIDName ;
  tempID.constant = "" ;
  gIDTemp.push_back( tempID ) ;
  checkIndex = checkIndex + 1 ;
  
  if ( gInput[checkIndex].name == "[" ) {
    checkIndex ++ ;
    if ( gInput[checkIndex].type == "Constant" ) {
      gIDTemp[gIDTemp.size()-1].constant = gInput[checkIndex].name ;
      checkIndex ++ ;
      if ( gInput[checkIndex].name == "]" ) {
        checkIndex ++ ;
        if ( gInput[checkIndex].name == ";" ) {
          checkIndex ++ ;
          return true ;
        } // if
        else if ( gInput[checkIndex].name == "," ) {
          while ( gInput[checkIndex].name == "," ) {
            checkIndex ++ ;
            if ( gInput[checkIndex].type == "identifier" ) {
              tmepIDName = gInput[checkIndex].name ;
              /*
              IDExistList = IDExist( gInput[checkIndex].name, IndexInIDList ) ;
              if ( IDExistList == true ) {
                gIDTemp.erase( gIDTemp.begin() + IndexInIDList ) ;
              } // if 
              */
              
              tempID.name = tmepIDName ;
              tempID.constant = "" ;
              gIDTemp.push_back( tempID ) ;
              checkIndex ++ ;
              if ( gInput[checkIndex].name == "[" ) {
                checkIndex ++ ;
                if ( gInput[checkIndex].type == "Constant" ) {
                  gIDTemp[gIDTemp.size()-1].constant = gInput[checkIndex].name ;
                  checkIndex ++ ;
                  if ( gInput[checkIndex].name == "]" ) {
                    checkIndex ++ ;
                  } // if
                } // if
              } // if
              else if ( gInput[checkIndex].name == "," ) {
                int a = 0 ;
              } // else if 
              else if ( gInput[checkIndex].name == ";" ) {
                checkIndex ++ ;
                return true ;
              } // else if 
              
            } // if
          } // while
          
          if ( gInput[checkIndex].name == ";" ) {
            checkIndex++ ;
            return true ; 
          } // if 
        } // else if
      } // if 
    } // if 
  } // if 
  else if ( gInput[checkIndex].name == "," ) {
    while ( gInput[checkIndex].name == "," ) {
      checkIndex ++ ;
      if ( gInput[checkIndex].type == "identifier" ) {
        tmepIDName = gInput[checkIndex].name ;
        /*
        IDExistList = IDExist( gInput[checkIndex].name, IndexInIDList ) ;
        if ( IDExistList == true ) {
          gIDTemp.erase( gIDTemp.begin() + IndexInIDList ) ;
        } // if 
        */
        
        tempID.name = tmepIDName ;
        tempID.constant = "" ;
        gIDTemp.push_back( tempID ) ;
        checkIndex ++ ;
        if ( gInput[checkIndex].name == "[" ) {
          checkIndex ++ ;
          if ( gInput[checkIndex].type == "Constant" ) {
            gIDTemp[gIDTemp.size()-1].constant = gInput[checkIndex].name ;
            checkIndex ++ ;
            if ( gInput[checkIndex].name == "]" ) {
              checkIndex ++ ;
            } // if
          } // if
        } // if
        else if ( gInput[checkIndex].name == "," ) {
          int a = 0 ;
        } // else if 
        else if ( gInput[checkIndex].name == ";" ) {
          checkIndex ++ ;
          return true ;
        } // else if 
        
      } // if
    } // while
    
    if ( gInput[checkIndex].name == ";" ) {
      checkIndex ++ ;
      return true ;
    } // if
  } // else if 
  else if ( gInput[checkIndex].name == ";" ) {
    checkIndex ++ ;
    return true ;
  } // else if 
  else {
    return false ;
  } // else 
    
  return false ;
    
} // FunctionRestOfDeclarators()

bool Declaration( int &checkIndex, bool &realQuit ) {
  CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
  // IDENTData temp ;
  // temp.type = gInput[checkIndex].type ;
  if ( TypeSpecifier( checkIndex, realQuit ) == true ) {
    CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
    if ( gInput[checkIndex].type == "identifier" ) {
      int tempIDListPut = checkIndex ;
      // temp.name = gInput[checkIndex].name ; 
      string tempIDListName = gInput[tempIDListPut].name ;
      // gIDTemp.push_back( temp ) ;
      checkIndex ++ ;
      CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
      // int tempIDListPut = checkIndex ; *** 
      // string tempIDListName = gInput[tempIDListPut].name ; ***
      if ( RestOfDeclarators( checkIndex, realQuit ) == true ) {
        if ( FunctionRestOfDeclarators( tempIDListPut, tempIDListName ) == true ) {
          int a = 0 ;
        } // if 
        
        return true ;
        // gIDTemp.push_back( temp ) ; HERE
      } // if 
      else 
        UnexpectedThrow( checkIndex ) ;
    } // if  
    else 
      UnexpectedThrow( checkIndex ) ;
  } // if 
  else {
    return false ;
  } // else 
    
  return false ;
  
} // Declaration()

bool Statement( int &checkIndex, bool &realQuit ) {
  CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
  if ( gInput[checkIndex].name == ";" ) {
    checkIndex ++ ;
    return true ;
  } // if 
  else if ( gInput[checkIndex].name == "return" ) {
    checkIndex ++ ;
    CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
    if ( Expression( checkIndex, realQuit ) == true ) {
      // checkIndex ++ ;
      CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
      if ( gInput[checkIndex].name == ";" ) {
        checkIndex ++ ;
        return true ;
      } // if 
      else 
        UnexpectedThrow( checkIndex ) ;
    } // if 
    else if ( gInput[checkIndex].name == ";" ) {
      checkIndex ++ ;
      return true ;
    } // else if 
    else 
      UnexpectedThrow( checkIndex ) ;
  } // else if 
  else if ( gInput[checkIndex].name == "if" ) {
    checkIndex ++ ;
    CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
    if ( gInput[checkIndex].name == "(" ) {
      checkIndex ++ ;
      CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
      if ( Expression( checkIndex, realQuit ) == true ) {
        CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
        if ( gInput[checkIndex].name == ")" ) {
          checkIndex ++ ;
          CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
          if ( Statement( checkIndex, realQuit ) == true ) {
            // CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
            if ( gInput[checkIndex].name == "else" ) {
              checkIndex ++ ;
              CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
              if ( Statement( checkIndex, realQuit ) == true ) {
                return true ;
              } // if 
              else 
                UnexpectedThrow( checkIndex ) ;                
            } // if 
            else 
              return true ;
          } // if 
          else 
            UnexpectedThrow( checkIndex ) ;
        } // if 
        else 
          UnexpectedThrow( checkIndex ) ;
      } // if
      else 
        UnexpectedThrow( checkIndex ) ;
    } // if 
    else 
      UnexpectedThrow( checkIndex ) ;
  } // else if 
  else if ( gInput[checkIndex].name == "while" ) {
    
    checkIndex ++ ;
    CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
    if ( gInput[checkIndex].name == "(" ) {
      checkIndex ++ ;
      CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
      if ( Expression( checkIndex, realQuit ) == true ) {
        CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
        if ( gInput[checkIndex].name == ")" ) {
          checkIndex ++ ;
          CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
          if ( Statement( checkIndex, realQuit ) == true ) 
            return true ; 
          else 
            UnexpectedThrow( checkIndex ) ;
        } // if 
        else 
          UnexpectedThrow( checkIndex ) ;
      } // if
      else 
        UnexpectedThrow( checkIndex ) ;
    } // if 
    else 
      UnexpectedThrow( checkIndex ) ;
  } // else if 
  else if ( gInput[checkIndex].name == "do" ) {
    checkIndex ++ ;
    CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
    if ( Statement( checkIndex, realQuit ) == true ) {
      CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
      if ( gInput[checkIndex].name == "while" ) {
        checkIndex ++ ;
        CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
        if ( gInput[checkIndex].name == "(" ) {
          checkIndex ++ ;
          CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
          if ( Expression( checkIndex, realQuit ) == true ) {
            CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
            if ( gInput[checkIndex].name == ")" ) {
              checkIndex ++ ;
              CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
              if ( gInput[checkIndex].name == ";" ) {
                checkIndex ++ ;
                return true ;
              } // if
              else 
                UnexpectedThrow( checkIndex ) ;
            } // if 
            else 
              UnexpectedThrow( checkIndex ) ;
          } // if 
          else 
            UnexpectedThrow( checkIndex ) ;
        } // if 
        else 
          UnexpectedThrow( checkIndex ) ;
      } // if 
      else 
        UnexpectedThrow( checkIndex ) ;
    } // if 
    else 
      UnexpectedThrow( checkIndex ) ;
  } // else if 
  else if ( CompoundStaement( checkIndex, realQuit ) == true ) {
    return true ;
  } // else if 
  else if ( Expression( checkIndex, realQuit ) == true ) {
    CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
    // printf("HERE") ;
    if ( gInput[checkIndex].name == ";" ) {
      // printf("!!%d!!",checkIndex ) ;
      checkIndex ++ ;
      return true ;
    } // if
    else 
      UnexpectedThrow( checkIndex ) ;
  } // else if 
  else {
    return false ;
  } // else 
    
  return false ;
  
} // Statement()

bool Expression( int &checkIndex, bool &realQuit ) {
  // printf("HERE") ;
  CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
  if ( BasicExpression( checkIndex, realQuit ) == true ) {
    CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
    while ( gInput[checkIndex].name == "," ) {
      checkIndex ++ ;
      CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
      if ( BasicExpression( checkIndex, realQuit ) == true ) 
        return true ;
      else 
        UnexpectedThrow( checkIndex ) ;
      
      // CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
    } // while
    
    return true ;
  } // if 
  else {
    return false ;
  } // else 
    
  return false ;
  
} // Expression()

bool BasicExpression( int &checkIndex, bool &realQuit ) {
  CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
  if ( gInput[checkIndex].type == "identifier" ) {
    if ( checkIndex + 1 < gInput.size() && gInput[checkIndex+1].name == "(" ) { // FUNC
      int checktemp = 0 ;
      bool inFunc = FunctionExist( gInput[checkIndex].name, checktemp ) ;
      // printf( "%s", gInput[checkIndex].name ) ;
      if ( inFunc == false ) 
        UndefinedThrow( checkIndex ) ;
    } // if 
    else { // NO FUNC
      int checktemp = 0 ;
      // printf("HERE %s%d ",gInput[checkIndex].name, checkIndex ) ;
      bool inTemp = IDExistTemp( gInput[checkIndex].name, checktemp ) ;
      bool inList = IDExist( gInput[checkIndex].name, checktemp ) ;
      // printf("%d%d", inTemp,inList ) ;
      if ( inTemp == false && inList == false ) {
        // printf("^%d^",checkIndex) ;
        UndefinedThrow( checkIndex ) ;
        // printf("&%d&",checkIndex) ;
      } // if 
    } // else  
      
    checkIndex ++ ;
    CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
    if ( RestOfIdentifierStartedBasicExp( checkIndex, realQuit ) == true ) 
      // printf("%dyes", checkIndex) ;
      return true ; 
    else 
      UnexpectedThrow( checkIndex ) ;
  } // if 
  else if ( gInput[checkIndex].type == "pp" || gInput[checkIndex].type == "mm" ) {
    checkIndex ++ ;
    CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
    if ( gInput[checkIndex].type == "identifier" ) {
      int checktemp = 0 ;
      bool inTemp = IDExistTemp( gInput[checkIndex].name, checktemp ) ;
      bool inList = IDExist( gInput[checkIndex].name, checktemp ) ;
      if ( inTemp == false && inList == false )
        UndefinedThrow( checkIndex ) ;
      
      checkIndex ++ ;
      CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
      if ( RestOfPPMMIdentifierStartedBasicExp( checkIndex, realQuit ) == true ) 
        return true ; 
      else 
        UnexpectedThrow( checkIndex ) ;
    } // if 
    else 
      UnexpectedThrow( checkIndex ) ;
  } // else if
  else if ( Sign( checkIndex, realQuit ) == true ) {
    CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
    while ( Sign( checkIndex, realQuit ) == true ) {
      CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
    } // while 
    
    if ( SignedUnaryExp( checkIndex, realQuit ) == true ) {
      CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
      if ( RomceAndRomloe( checkIndex, realQuit ) == true )
        return true ;
      else 
        UnexpectedThrow( checkIndex ) ;
    } // if 
    else 
      UnexpectedThrow( checkIndex ) ;
  } // else if 
  else if ( gInput[checkIndex].type == "Constant" ) {
    checkIndex ++ ;
    CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
    if ( RomceAndRomloe( checkIndex, realQuit ) == true ) 
      return true ;
    else 
      UnexpectedThrow( checkIndex ) ;
  } // else if 
  else if ( gInput[checkIndex].name == "(" ) {
    checkIndex ++ ;
    CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
    if ( Expression( checkIndex, realQuit ) == true ) {
      CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
      if ( gInput[checkIndex].name == ")" ) {
        checkIndex ++ ;
        CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
        if ( RomceAndRomloe( checkIndex, realQuit ) == true ) 
          return true ;
        else 
          UnexpectedThrow( checkIndex ) ;
      } // if 
      else 
        UnexpectedThrow( checkIndex ) ;
    } // if 
    else 
      UnexpectedThrow( checkIndex ) ;
  } // else if 
  else {
    return false ;
  } // else 
    
  return false ;
  
} // BasicExpression()

bool RestOfIdentifierStartedBasicExp( int &checkIndex, bool &realQuit ) {
  CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
  if ( gInput[checkIndex].name == "(" ) {
    checkIndex ++ ;
    CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
    if ( ActualParameterList( checkIndex, realQuit ) == true ) 
      CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
    
    if ( gInput[checkIndex].name == ")" ) {
      checkIndex ++ ;
      CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
      if ( RomceAndRomloe( checkIndex, realQuit ) == true ) 
        return true ;
      else 
        UnexpectedThrow( checkIndex ) ;
    } // if
    else 
      UnexpectedThrow( checkIndex ) ;
  } // if
  else if ( gInput[checkIndex].name == "[" ) {
    checkIndex ++ ;
    CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
    if ( Expression( checkIndex, realQuit ) == true ) {
      CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
      if ( gInput[checkIndex].name == "]" ) {
        checkIndex ++ ;
        CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
        if ( AssignmentOperator( checkIndex, realQuit ) == true ) {
          CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
          if ( BasicExpression( checkIndex, realQuit ) == true ) 
            return true ;
          else 
            UnexpectedThrow( checkIndex ) ;
        } // if 
        else if ( gInput[checkIndex].type == "pp" || gInput[checkIndex].type == "mm" ) {
          checkIndex ++ ;
          CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
          if ( RomceAndRomloe( checkIndex, realQuit ) == true ) 
            return true ;
          else 
            UnexpectedThrow( checkIndex ) ;
        } // else if 
        else if ( RomceAndRomloe( checkIndex, realQuit ) == true ) {
          return true ;
        } // else if 
        else 
          UnexpectedThrow( checkIndex ) ;
      } // if 
      else 
        UnexpectedThrow( checkIndex ) ; 
    } // if 
    else 
      UnexpectedThrow( checkIndex ) ;
  } // else if 
  else if ( AssignmentOperator( checkIndex, realQuit ) == true ) {
    CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
    if ( BasicExpression( checkIndex, realQuit ) == true ) {
      // printf("GOOD") ;
      return true ;
    } // if 
    else 
      UnexpectedThrow( checkIndex ) ;
  } // else if
  else if ( gInput[checkIndex].type == "pp" || gInput[checkIndex].type == "mm" ) {
    checkIndex ++ ;
    CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
    if ( RomceAndRomloe( checkIndex, realQuit ) == true ) 
      return true ;
    else 
      UnexpectedThrow( checkIndex ) ;
  } // else if
  else if ( RomceAndRomloe( checkIndex, realQuit ) == true ) {
    return true ;
  } // else if
  /*
  else if ( gInput[checkIndex].name == "(" ) {
    checkIndex ++ ;
    CheckUnrecognizeToken( gInput[checkIndex].name ,  checkIndex ) ;
    if ( ActualParameterList( checkIndex, realQuit ) == true ) 
      CheckUnrecognizeToken( gInput[checkIndex].name ,  checkIndex ) ;
    
    if ( gInput[checkIndex].name == ")" ) {
      checkIndex ++ ;
      CheckUnrecognizeToken( gInput[checkIndex].name ,  checkIndex ) ;
      if ( RomceAndRomloe( checkIndex, realQuit ) == true ) 
        return true ;
      else 
        UnexpectedThrow( checkIndex ) ;
    } // if
    else 
      UnexpectedThrow( checkIndex ) ;
  } // else if
  */
  else {
    return false ;
  } // else 
    
  return false ;
  
} // RestOfIdentifierStartedBasicExp()

bool RestOfPPMMIdentifierStartedBasicExp( int &checkIndex, bool &realQuit ) {
  CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
  if ( gInput[checkIndex].name == "[" ) {
    checkIndex ++ ;
    CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
    if ( Expression( checkIndex, realQuit ) == true ) {
      CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
      if ( gInput[checkIndex].name == "]" ) {
        checkIndex ++ ;
        CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
        if ( RomceAndRomloe( checkIndex, realQuit ) == true ) 
          return true ;
        else 
          UnexpectedThrow( checkIndex ) ;
      } // if 
      else 
        UnexpectedThrow( checkIndex ) ;
    } // if 
    else 
      UnexpectedThrow( checkIndex ) ;
  } // if 
  else if ( RomceAndRomloe( checkIndex, realQuit ) == true )
    return true ;
  else {
    return false ;
  } // else 
    
  return false ;
  
} // RestOfPPMMIdentifierStartedBasicExp()

bool Sign( int &checkIndex, bool &realQuit ) {
  CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
  if ( gInput[checkIndex].name == "+" || gInput[checkIndex].name == "-" || gInput[checkIndex].name == "!" )
    checkIndex ++ ;
  else 
    return false ;
  
  return true ;
  
} // Sign()

bool ActualParameterList( int &checkIndex, bool &realQuit ) {
  CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
  if ( BasicExpression( checkIndex, realQuit ) == true ) {
    // CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
    while ( gInput[checkIndex].name == "," ) {
      checkIndex ++ ;
      CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
      if ( BasicExpression( checkIndex, realQuit ) == true )
        CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
      else 
        UnexpectedThrow( checkIndex ) ;
      
      CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
    } // while 
    
    return true ;
  } // if 
  else {
    return false ;
  } // else 
    
  return false ;
  
} // ActualParameterList()

bool AssignmentOperator( int &checkIndex, bool &realQuit ) {
  CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
  if ( gInput[checkIndex].name == "=" || gInput[checkIndex].type == "te" || 
       gInput[checkIndex].type == "re" || gInput[checkIndex].type == "pe" ||
       gInput[checkIndex].type == "de" || gInput[checkIndex].type == "me" ) {
    checkIndex ++ ;
    return true ;
  } // if 
  else {
    return false ;
  } // else 
    
  return false ;
  
} // AssignmentOperator()

bool RomceAndRomloe( int &checkIndex, bool &realQuit ) {
  CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
  if ( RestOfMaybeLogicalOrExp( checkIndex, realQuit ) == true ) {
    CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
    if ( gInput[checkIndex].name == "?" ) {
      checkIndex ++ ;
      CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
      if ( BasicExpression( checkIndex, realQuit ) == true ) {
        CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
        if ( gInput[checkIndex].name == ":" ) {
          checkIndex ++ ;
          CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
          if ( BasicExpression( checkIndex, realQuit ) == true ) 
            return true ;
          else 
            UnexpectedThrow( checkIndex ) ;
        } // if
        else 
          UnexpectedThrow( checkIndex ) ;
      } // if 
      else 
        UnexpectedThrow( checkIndex ) ;
    } // if 
    else 
      return true ;
  } // if 
  else {
    return false ;
  } // else 
    
  return false ;
  
} // RomceAndRomloe()

bool RestOfMaybeLogicalOrExp( int &checkIndex, bool &realQuit ) {
  CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
  if ( RestOfMaybeLogicalAndExp( checkIndex, realQuit ) == true ) {
    CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
    while ( gInput[checkIndex].type == "or" ) {
      checkIndex ++ ;
      CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
      if ( MaybeLogicalAndExp( checkIndex, realQuit ) == true ) 
        CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
      else 
        UnexpectedThrow( checkIndex ) ;
      
      CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
    } // while 
    
    return true ;
  } // if 
  else {
    return false ;
  } // else 
    
  return false ;
  
} // RestOfMaybeLogicalOrExp()

bool MaybeLogicalAndExp( int &checkIndex, bool &realQuit ) { 
  CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
  if ( MaybeBitOrExp( checkIndex, realQuit ) == true ) {
    CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
    while ( gInput[checkIndex].type == "and" ) {
      checkIndex ++ ;
      CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
      if ( MaybeBitOrExp( checkIndex, realQuit ) == true ) 
        CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
      else 
        UnexpectedThrow( checkIndex ) ;
      
      CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
    } // while 
    
    return true ;
  } // if 
  else {
    return false ;
  } // else 
    
  return false ;
  
} // MaybeLogicalAndExp()

bool RestOfMaybeLogicalAndExp( int &checkIndex, bool &realQuit ) {
  CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
  if ( RestOfMaybeBitOrExp( checkIndex, realQuit ) == true ) {
    CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
    while ( gInput[checkIndex].type == "and" ) {
      checkIndex ++ ;
      CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
      if ( MaybeBitOrExp( checkIndex, realQuit ) == true ) 
        CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
      else 
        UnexpectedThrow( checkIndex ) ;
      
      CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
    } // while 
    
    return true ;
  } // if 
  else {
    return false ;
  } // else 
    
  return false ;
  
} // RestOfMaybeLogicalAndExp()

bool MaybeBitOrExp( int &checkIndex, bool &realQuit ) {
  CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
  if ( MaybeBitExOrExp( checkIndex, realQuit ) == true ) {
    CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
    while ( gInput[checkIndex].name == "|" ) {
      checkIndex ++ ;
      CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
      if ( MaybeBitExOrExp( checkIndex, realQuit ) == true ) 
        CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
      else 
        UnexpectedThrow( checkIndex ) ;
      
      CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
    } // while 
    
    return true ;
  } // if 
  else {
    return false ;
  } // else 
    
  return false ;
  
} // MaybeBitOrExp()

bool RestOfMaybeBitOrExp( int &checkIndex, bool &realQuit ) {
  CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
  if ( RestOfMaybeBitExOrExp( checkIndex, realQuit ) == true ) {
    CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
    while ( gInput[checkIndex].name == "|" ) {
      checkIndex ++ ;
      CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
      if ( MaybeBitExOrExp( checkIndex, realQuit ) == true ) 
        CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
      else 
        UnexpectedThrow( checkIndex ) ;
      
      CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
    } // while 
    
    return true ;
  } // if 
  else {
    return false ;
  } // else 
    
  return false ;
  
} // RestOfMaybeBitOrExp()

bool MaybeBitExOrExp( int &checkIndex, bool &realQuit ) {
  CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
  if ( MaybeBitAndExp( checkIndex, realQuit ) == true ) {
    CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
    while ( gInput[checkIndex].name == "^" ) {
      checkIndex ++ ;
      CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
      if ( MaybeBitAndExp( checkIndex, realQuit ) == true ) 
        CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
      else 
        UnexpectedThrow( checkIndex ) ;
      
      CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
    } // while 
    
    return true ;
  } // if 
  else {
    return false ;
  } // else 
    
  return false ;
  
} // MaybeBitExOrExp()

bool RestOfMaybeBitExOrExp( int &checkIndex, bool &realQuit ) {
  CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
  if ( RestOfMaybeBitAndExp( checkIndex, realQuit ) == true ) {
    CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
    while ( gInput[checkIndex].name == "^" ) {
      checkIndex ++ ;
      CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
      if ( MaybeBitAndExp( checkIndex, realQuit ) == true ) 
        CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
      else 
        UnexpectedThrow( checkIndex ) ;
      
      CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
    } // while 
    
    return true ;
  } // if 
  else {
    return false ;
  } // else 
    
  return false ;
  
} // RestOfMaybeBitExOrExp()

bool MaybeBitAndExp( int &checkIndex, bool &realQuit ) {
  CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
  if ( MaybeEqualityExp( checkIndex, realQuit ) == true ) {
    CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
    while ( gInput[checkIndex].name == "&" ) {
      checkIndex ++ ;
      CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
      if ( MaybeEqualityExp( checkIndex, realQuit ) == true ) 
        CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
      else 
        UnexpectedThrow( checkIndex ) ;
      
      CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
    } // while 
    
    return true ;
  } // if 
  else {
    return false ;
  } // else 
    
  return false ;
   
} // MaybeBitAndExp()

bool RestOfMaybeBitAndExp( int &checkIndex, bool &realQuit ) {
  CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
  if ( RestOfMaybeEqualityExp( checkIndex, realQuit ) == true ) {
    CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
    while ( gInput[checkIndex].name == "&" ) {
      checkIndex ++ ;
      CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
      if ( MaybeEqualityExp( checkIndex, realQuit ) == true ) 
        CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
      else 
        UnexpectedThrow( checkIndex ) ;
      
      CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
    } // while 
    
    return true ;
  } // if 
  else {
    return false ;
  } // else 
    
  return false ;
  
} // RestOfMaybeBitAndExp()

bool MaybeEqualityExp( int &checkIndex, bool &realQuit ) {
  CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
  if ( MaybeRelationalExp( checkIndex, realQuit ) == true ) {
    CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
    while ( gInput[checkIndex].type == "eq" || gInput[checkIndex].type == "neq" ) {
      checkIndex ++ ;
      if ( MaybeRelationalExp( checkIndex, realQuit ) == true ) 
        CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
      else 
        UnexpectedThrow( checkIndex ) ;
      
      CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
    } // while
    
    return true ;
  } // if 
  else {
    return false ;
  } // else 
    
  return false ;
  
} // MaybeEqualityExp()

bool RestOfMaybeEqualityExp( int &checkIndex, bool &realQuit ) {
  CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
  if ( RestOfMaybeRelationalExp( checkIndex, realQuit ) == true ) {
    CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
    while ( gInput[checkIndex].type == "eq" || gInput[checkIndex].type == "neq" ) {
      checkIndex ++ ;
      if ( MaybeRelationalExp( checkIndex, realQuit ) == true ) 
        CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
      else 
        UnexpectedThrow( checkIndex ) ;
      
      CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
    } // while
    
    return true ;
  } // if 
  else {
    return false ;
  } // else 
    
  return false ;
  
} // RestOfMaybeEqualityExp()

bool MaybeRelationalExp( int &checkIndex, bool &realQuit ) {
  CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
  if ( MaybeShiftExp( checkIndex, realQuit ) == true ) {
    CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
    while ( gInput[checkIndex].name == ">" || gInput[checkIndex].name == "<" ||
            gInput[checkIndex].type == "le" || gInput[checkIndex].type == "ge" ) {
      checkIndex ++ ;
      if ( MaybeShiftExp( checkIndex, realQuit ) == true ) 
        CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
      else 
        UnexpectedThrow( checkIndex ) ;
      
      CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
    } // while
    
    return true ;
  } // if 
  else {
    return false ;
  } // else 
    
  return false ;
  
} // MaybeRelationalExp()

bool RestOfMaybeRelationalExp( int &checkIndex, bool &realQuit ) {
  CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
  if ( RestOfMaybeShiftExp( checkIndex, realQuit ) == true ) {
    CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
    while ( gInput[checkIndex].name == ">" || gInput[checkIndex].name == "<" ||
            gInput[checkIndex].type == "le" || gInput[checkIndex].type == "ge" ) {
      checkIndex ++ ;
      if ( MaybeShiftExp( checkIndex, realQuit ) == true ) 
        CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
      else 
        UnexpectedThrow( checkIndex ) ;
      
      CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
    } // while
    
    return true ;
  } // if 
  else {
    return false ;
  } // else 
    
  return false ;
  
} // RestOfMaybeRelationalExp()

bool MaybeShiftExp( int &checkIndex, bool &realQuit ) {
  CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
  if ( MaybeAdditiveExp( checkIndex, realQuit ) == true ) {
    CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
    while ( gInput[checkIndex].type == "ls" || gInput[checkIndex].type == "rs" ) {
      checkIndex ++ ;
      if ( MaybeAdditiveExp( checkIndex, realQuit ) == true ) 
        CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
      else 
        UnexpectedThrow( checkIndex ) ;
      
      CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
    } // while
    
    return true ;
  } // if 
  else {
    return false ;
  } // else 
    
  return false ;
  
} // MaybeShiftExp()

bool RestOfMaybeShiftExp( int &checkIndex, bool &realQuit ) {
  CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
  if ( RestOfMaybeAdditiveExp( checkIndex, realQuit ) == true ) {
    CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
    while ( gInput[checkIndex].type == "ls" || gInput[checkIndex].type == "rs" ) {
      checkIndex ++ ;
      if ( MaybeAdditiveExp( checkIndex, realQuit ) == true ) 
        CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
      else 
        UnexpectedThrow( checkIndex ) ;
      
      CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
    } // while
    
    return true ;
  } // if 
  else {
    return false ;
  } // else 
    
  return false ;
  
} // RestOfMaybeShiftExp()

bool MaybeAdditiveExp( int &checkIndex, bool &realQuit ) {
  CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
  if ( MaybeMultExp( checkIndex, realQuit ) == true ) {
    CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
    while ( gInput[checkIndex].name == "+" || gInput[checkIndex].name == "-" ) {
      checkIndex ++ ;
      if ( MaybeMultExp( checkIndex, realQuit ) == true ) 
        CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
      else 
        UnexpectedThrow( checkIndex ) ;
      
      CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
    } // while
    
    return true ;
  } // if 
  else {
    return false ;
  } // else 
    
  return false ;
  
} // MaybeAdditiveExp()

bool RestOfMaybeAdditiveExp( int &checkIndex, bool &realQuit ) {
  CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
  if ( RestOfMaybeMultExp( checkIndex, realQuit ) == true ) {
    CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
    while ( gInput[checkIndex].name == "+" || gInput[checkIndex].name == "-" ) {
      checkIndex ++ ;
      if ( MaybeMultExp( checkIndex, realQuit ) == true ) 
        CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
      else 
        UnexpectedThrow( checkIndex ) ;
      
      CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
    } // while
    
    return true ;
  } // if 
  else {
    return false ;
  } // else 
    
  return false ;
  
} // RestOfMaybeAdditiveExp()

bool MaybeMultExp( int &checkIndex, bool &realQuit ) {
  CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
  if ( UnaryExp( checkIndex, realQuit ) == true ) {
    CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
    if ( RestOfMaybeMultExp( checkIndex, realQuit ) == true )
      return true ;
    else 
      UnexpectedThrow( checkIndex ) ;
  } // if 
  else {
    return false ;
  } // else 
    
  return false ;
  
} // MaybeMultExp()

bool RestOfMaybeMultExp( int &checkIndex, bool &realQuit ) {
  // could be empty !!!!!!
  CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
  if ( gInput[checkIndex].name == "*" || gInput[checkIndex].name == "/" || gInput[checkIndex].name == "%" ) {
    while ( gInput[checkIndex].name == "*" || gInput[checkIndex].name == "/" ||
            gInput[checkIndex].name == "%" ) {
      checkIndex ++ ;
      CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
      if ( UnaryExp( checkIndex, realQuit ) == true )
        CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
      else 
        UnexpectedThrow( checkIndex ) ;
        // return false ;
        
      CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
    } // while
    
    return true ;
  } // if 
  else {
    return true ;
  } // else 
    
  return false ;
  
} // RestOfMaybeMultExp()

bool UnaryExp( int &checkIndex, bool &realQuit ) {
  CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
  if ( Sign( checkIndex, realQuit ) == true ) {
    CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
    while ( Sign( checkIndex, realQuit ) == true ) {
      CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
    } // while 
    
    if ( SignedUnaryExp( checkIndex, realQuit ) == true )
      // CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
      return true ;
    else 
      UnexpectedThrow( checkIndex ) ;
  } // if 
  else if ( UnsignedUnaryExp( checkIndex, realQuit ) == true ) {
    // CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
    return true ;
  } // else if 
  else if ( gInput[checkIndex].type == "pp" || gInput[checkIndex].type == "mm" ) {
    checkIndex ++ ;
    CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
    if ( gInput[checkIndex].type == "identifier" ) {
      int checktemp = 0 ;
      bool inTemp = IDExistTemp( gInput[checkIndex].name, checktemp ) ;
      bool inList = IDExist( gInput[checkIndex].name, checktemp ) ;
      if ( inTemp == false && inList == false )
        UndefinedThrow( checkIndex ) ;
      
      checkIndex ++ ;
      CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
      if ( gInput[checkIndex].name == "[" ) {
        checkIndex ++ ;
        CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
        if ( Expression( checkIndex, realQuit ) == true ) {
          CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
          if ( gInput[checkIndex].name == "]" ) {
            checkIndex ++ ;
            return true ;
          } // if 
          else 
            UnexpectedThrow( checkIndex ) ;
        } // if 
        else 
          UnexpectedThrow( checkIndex ) ;
      } // if 
      else 
        return true ;
    } // if 
    else 
      UnexpectedThrow( checkIndex ) ;
  } // else if 
  else {
    return false ;
  } // else 
    
  return false ;
  
} // UnaryExp()

bool SignedUnaryExp( int &checkIndex, bool &realQuit ) {
  CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
  if ( gInput[checkIndex].type == "identifier" ) {
    if ( checkIndex + 1 < gInput.size() && gInput[checkIndex+1].name == "(" ) { // FUNC
      int checktemp = 0 ;
      bool inFunc = FunctionExist( gInput[checkIndex].name, checktemp ) ;
      if ( inFunc == false )
        UndefinedThrow( checkIndex ) ;
    } // if 
    else { // NO FUNC
      int checktemp = 0 ;
      bool inTemp = IDExistTemp( gInput[checkIndex].name, checktemp ) ;
      bool inList = IDExist( gInput[checkIndex].name, checktemp ) ;
      if ( inTemp == false && inList == false )
        UndefinedThrow( checkIndex ) ;
    } // else  
    
    checkIndex ++ ;
    CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
    if ( gInput[checkIndex].name == "(" ) {
      checkIndex ++ ;
      CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
      if ( gInput[checkIndex].name == ")" ) {
        checkIndex ++ ;
        return true ;
      } // if 
      else if ( ActualParameterList( checkIndex, realQuit ) == true ) {
        CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
        if ( gInput[checkIndex].name == ")" ) {
          checkIndex ++ ;
          return true ;
        } // if 
        else 
          UnexpectedThrow( checkIndex ) ;
      } // else if 
      else 
        UnexpectedThrow( checkIndex ) ;
    } // if 
    else if ( gInput[checkIndex].name == "[" ) {
      checkIndex ++ ;
      CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
      if ( Expression( checkIndex, realQuit ) == true ) {
        CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
        if ( gInput[checkIndex].name == "]" ) {
          checkIndex ++ ;
          return true ;
        } // if 
        else 
          UnexpectedThrow( checkIndex ) ;
      } // if 
      else 
        UnexpectedThrow( checkIndex ) ;
    } // else if
    else 
      return true ;
    
  } // if 
  else if ( gInput[checkIndex].type == "Constant" ) {
    checkIndex ++ ;
    return true ;
  } // else if 
  else if ( gInput[checkIndex].name == "(" ) {
    checkIndex ++ ;
    if ( Expression( checkIndex, realQuit ) == true ) {
      CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
      if ( gInput[checkIndex].name == ")" ) {
        checkIndex ++ ;
        return true ;
      } // if 
      else 
        UnexpectedThrow( checkIndex ) ;
    } // if 
    else 
      UnexpectedThrow( checkIndex ) ;
  } // else if 
  else {
    return false ;
  } // else 
    
  return false ;
  
} // SignedUnaryExp()

bool UnsignedUnaryExp( int &checkIndex, bool &realQuit ) {
  CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
  if ( gInput[checkIndex].type == "identifier" ) {
    if ( checkIndex + 1 < gInput.size() && gInput[checkIndex+1].name == "(" ) { // FUNC
      int checktemp = 0 ;
      bool inFunc = FunctionExist( gInput[checkIndex].name, checktemp ) ;
      if ( inFunc == false )
        UndefinedThrow( checkIndex ) ;
    } // if 
    else { // NO FUNC
      int checktemp = 0 ;
      bool inTemp = IDExistTemp( gInput[checkIndex].name, checktemp ) ;
      bool inList = IDExist( gInput[checkIndex].name, checktemp ) ;
      if ( inTemp == false && inList == false )
        UndefinedThrow( checkIndex ) ;
    } // else  
      
    checkIndex ++ ;
    if ( gInput[checkIndex].name == "(" ) {
      checkIndex ++ ;
      CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
      if ( gInput[checkIndex].name == ")" ) {
        checkIndex ++ ;
        return true ;
      } // if 
      else if ( ActualParameterList( checkIndex, realQuit ) == true ) {
        CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
        if ( gInput[checkIndex].name == ")" ) {
          checkIndex ++ ;
          return true ;
        } // if 
        else 
          UnexpectedThrow( checkIndex ) ;
      } // else if 
      else 
        UnexpectedThrow( checkIndex ) ;
    } // if 
    else if ( gInput[checkIndex].name == "[" ) {
      checkIndex ++ ;
      CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
      if ( Expression( checkIndex, realQuit ) == true ) {
        CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
        if ( gInput[checkIndex].name == "]" ) {
          checkIndex ++ ;
          if ( gInput[checkIndex].type == "pp" || gInput[checkIndex].type == "mm" ) {
            checkIndex ++ ;
            return true ;
          } // if 
          else 
            return true ;
        } // if 
        else 
          UnexpectedThrow( checkIndex ) ;
      } // if 
      else 
        UnexpectedThrow( checkIndex ) ;
    } // else if
    else if ( gInput[checkIndex].type == "pp" || gInput[checkIndex].type == "mm" ) {
      checkIndex ++ ;
      return true ;
    } // else if
    else 
      return true ;
    
  } // if 
  else if ( gInput[checkIndex].type == "Constant" ) {
    checkIndex ++ ;
    return true ;
  } // else if 
  else if ( gInput[checkIndex].name == "(" ) {
    checkIndex ++ ;
    if ( Expression( checkIndex, realQuit ) == true ) {
      CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
      if ( gInput[checkIndex].name == ")" ) {
        checkIndex ++ ;
        return true ;
      } // if 
      else 
        UnexpectedThrow( checkIndex ) ;
    } // if 
    else 
      UnexpectedThrow( checkIndex ) ;
  } // else if 
  else {
    return false ;
  } // else 
    
  return false ;
  
} // UnsignedUnaryExp()

// ------------------------------------------------------------------

bool DoDefinition( int &checkIndex ) {
  int indexInFuncList = -1 ;
  int indexInIDList = -1 ;
  bool iDExistFunction = false ;
  bool iDExistList = false ;
  int head = checkIndex ;
  int tail = checkIndex ;
  string whichType ;
  if ( gInput[checkIndex].type == "void" ) {
    checkIndex ++ ;
    CheckUnrecognizeToken( gInput[checkIndex].name, checkIndex ) ;
    if ( gInput[checkIndex].type == "identifier" ) {
      iDExistFunction = FunctionExist( gInput[checkIndex].name, indexInFuncList ) ;
      checkIndex ++ ;
      if ( DoFunctionDefinitionWithoutID( checkIndex ) == true ) {
        tail = checkIndex - 1 ;
        SaveFunction( head, tail, iDExistFunction, indexInFuncList ) ;
        if ( iDExistFunction == true ) 
          printf( "> New definition of %s() entered ...\n", gInput[head+1].name.c_str() ) ;
        else 
          printf( "> Definition of %s() entered ...\n", gInput[head+1].name.c_str() ) ;
        return true ;
      } // if 
      else 
        UnexpectedThrow( checkIndex ) ;
    } // if 
    else 
      UnexpectedThrow( checkIndex ) ;
  } // if
  else if ( DoTypeSpecifier( checkIndex, whichType ) == true ) {
    if ( gInput[checkIndex].type == "identifier" ) {
      iDExistFunction = FunctionExist( gInput[checkIndex].name, indexInFuncList ) ;
      iDExistList = IDExist( gInput[checkIndex].name, indexInIDList ) ;
      string tmepIDName = gInput[checkIndex].name ;
      checkIndex ++ ;
      bool isFunction = false ;
      // printf("NICE") ;
      if ( DoFunctionDefinitionOrDeclarators( checkIndex, isFunction ) == true ) {
        // printf("NICE") ;
        if ( isFunction == true ) {
          tail = checkIndex - 1 ;
          SaveFunction( head, tail, iDExistFunction, indexInFuncList ) ;
          // printf( "*%s*", gIDList[IndexInIDList].name.c_str() ) ;
          if ( iDExistFunction == true ) 
            printf( "> New definition of %s() entered ...\n", gInput[head+1].name.c_str() ) ;
          else 
            printf( "> Definition of %s() entered ...\n", gInput[head+1].name.c_str() ) ;
        } // if 
        else {
          /*
          if ( IDExistList == true ) {
            gIDList.erase( gIDList.begin() + IndexInIDList ) ;
            printf( "> New definition of %s entered ...\n", tmepIDName.c_str() ) ;
          } // if 
          else 
            printf( "> Definition of %s entered ...\n", tmepIDName.c_str() ) ;
          
          IDENTData tempID ;
          tempID.name = tmepIDName ;
          gIDList.push_back( tempID ) ;
          */ 
          tail = checkIndex - 1 ;
          DoAgainRestOfDeclarators( head, iDExistList, indexInIDList, tmepIDName, whichType ) ;
        } // else 
          
        return true ;
      } // if 
      else {
        // printf("error") ;
        UnexpectedThrow( checkIndex ) ;
      } // else 
    } // if 
    else 
      UnexpectedThrow( checkIndex ) ;
  } // else if 
  else {
    return false ;
  } // else 
  
  return false ;

} // DoDefinition()

bool DoTypeSpecifier( int &checkIndex, string &whichType ) {
  if ( gInput[checkIndex].name == "int" || 
       gInput[checkIndex].name == "char" || gInput[checkIndex].name == "float" || 
       gInput[checkIndex].name == "string" || gInput[checkIndex].name == "bool" )  {
    whichType = gInput[checkIndex].name ;
    checkIndex ++ ;
    return true ;
  } // if
  else 
    return false ;
} // DoTypeSpecifier()

bool DoFunctionDefinitionOrDeclarators( int &checkIndex, bool &isFunction ) {
  int head = checkIndex - 2 ;
  int indexInIDList = -1 ;
  string tmepIDName = gInput[checkIndex-1].name ;
  bool iDExistList = IDExist( tmepIDName, indexInIDList ) ;
  string whichType = gInput[checkIndex-2].name ;
  if ( gInput[checkIndex].name == "(" ) {
    if ( DoFunctionDefinitionWithoutID( checkIndex ) == true ) {
      isFunction = true ;
      return true ;
    } // if
    else {
      isFunction = false ;
      return false ;
    } // else 
  } // if 
  else if ( DoRestOfDeclarators( checkIndex ) == true ) {
  // else if ( DoAgainRestOfDeclarators( head, iDExistList, 
  // indexInIDList, tmepIDName, whichType ) == true ) {
    isFunction = false ;
    return true ;
  } // else if 
  else {
    return false ;
  } // else
    
  return false ;
    
} // DoFunctionDefinitionOrDeclarators()

bool DoRestOfDeclarators( int &checkIndex ) {
  IDENTData temp ; 
  
  if ( gInput[checkIndex].name == "[" ) {
    checkIndex ++ ;
    if ( gInput[checkIndex].type == "Constant" ) {
      checkIndex ++ ;
      if ( gInput[checkIndex].name == "]" ) {
        checkIndex ++ ;
        if ( gInput[checkIndex].name == ";" ) {
          checkIndex ++ ;
          return true ;
        } // if
        else if ( gInput[checkIndex].name == "," ) {
          while ( gInput[checkIndex].name == "," ) {
            checkIndex ++ ;
            if ( gInput[checkIndex].type == "identifier" ) {
              temp.name = gInput[checkIndex].name ; 
              gIDTemp.push_back( temp ) ;
              checkIndex ++ ;
              if ( gInput[checkIndex].name == "[" ) {
                checkIndex ++ ;
                if ( gInput[checkIndex].type == "Constant" ) {
                  checkIndex ++ ;
                  if ( gInput[checkIndex].name == "]" ) {
                    checkIndex ++ ;
                  } // if
                  else 
                    UnexpectedThrow( checkIndex ) ;
                } // if
                else 
                  UnexpectedThrow( checkIndex ) ;
              } // if
              else if ( gInput[checkIndex].name == "," ) {
                int a = 0 ;
              } // else if 
              else if ( gInput[checkIndex].name == ";" ) {
                checkIndex ++ ;
                return true ;
              } // else if 
              else 
                UnexpectedThrow( checkIndex ) ;
            } // if
            else 
              UnexpectedThrow( checkIndex ) ;
          } // while
          
          if ( gInput[checkIndex].name == ";" ) {
            checkIndex++ ;
            return true ; 
          } // if 
          else 
            UnexpectedThrow( checkIndex ) ;
        } // else if
        else 
          UnexpectedThrow( checkIndex ) ;
        
      } // if 
      else 
        UnexpectedThrow( checkIndex ) ;
    } // if 
    else 
      UnexpectedThrow( checkIndex ) ;
  } // if 
  else if ( gInput[checkIndex].name == "," ) {
    while ( gInput[checkIndex].name == "," ) {
      checkIndex ++ ;
      if ( gInput[checkIndex].type == "identifier" ) {
        temp.name = gInput[checkIndex].name ; 
        gIDTemp.push_back( temp ) ;
        checkIndex ++ ;
        if ( gInput[checkIndex].name == "[" ) {
          checkIndex ++ ;
          if ( gInput[checkIndex].type == "Constant" ) {
            checkIndex ++ ;
            if ( gInput[checkIndex].name == "]" ) {
              checkIndex ++ ;
            } // if
            else 
              UnexpectedThrow( checkIndex ) ;
          } // if
          else 
            UnexpectedThrow( checkIndex ) ;
        } // if
        else if ( gInput[checkIndex].name == "," ) {
          int a = 0 ;
        } // else if 
        else if ( gInput[checkIndex].name == ";" ) {
          checkIndex ++ ;
          return true ;
        } // else if 
        else 
          UnexpectedThrow( checkIndex ) ;
      } // if
      else 
        UnexpectedThrow( checkIndex ) ;

    } // while
    
    if ( gInput[checkIndex].name == ";" ) {
      checkIndex ++ ;
      return true ;
    } // if
    else 
      UnexpectedThrow( checkIndex ) ;
  } // else if 
  else if ( gInput[checkIndex].name == ";" ) {
    checkIndex ++ ;
    return true ;
  } // else if 
  else {
    return false ;
  } // else 
    
  return false ;
  
} // DoRestOfDeclarators()

bool DoAgainRestOfDeclarators( int &checkIndex, bool IDExistList, int IndexInIDList,
                               string tmepIDName, string whichType ) {
  if ( IDExistList == true ) {
    gIDList.erase( gIDList.begin() + IndexInIDList ) ;
    printf( "> New definition of %s entered ...\n", tmepIDName.c_str() ) ;
  } // if 
  else {
    printf( "> Definition of %s entered ...\n", tmepIDName.c_str() ) ;
  } // else 
    
  IDENTData tempID ;
  tempID.name = tmepIDName ;
  tempID.type = whichType ;
  tempID.constant = "" ;
  gIDList.push_back( tempID ) ;
  
  checkIndex = checkIndex + 2 ;
  
  if ( gInput[checkIndex].name == "[" ) {
    checkIndex ++ ;
    if ( gInput[checkIndex].type == "Constant" ) {
      // gIDList[gIDList.size()-1].name = gIDList[gIDList.size()-1].name + "[ " ;
      // gIDList[gIDList.size()-1].name = gIDList[gIDList.size()-1].name + gInput[checkIndex].name + " ]" ;
      gIDList[gIDList.size()-1].constant = gInput[checkIndex].name ;
      checkIndex ++ ;
      if ( gInput[checkIndex].name == "]" ) {
        checkIndex ++ ;
        if ( gInput[checkIndex].name == ";" ) {
          checkIndex ++ ;
          return true ;
        } // if
        else if ( gInput[checkIndex].name == "," ) {
          while ( gInput[checkIndex].name == "," ) {
            checkIndex ++ ;
            if ( gInput[checkIndex].type == "identifier" ) {
              tmepIDName = gInput[checkIndex].name ;
              IDExistList = IDExist( gInput[checkIndex].name, IndexInIDList ) ;
              if ( IDExistList == true ) {
                gIDList.erase( gIDList.begin() + IndexInIDList ) ;
                printf( "New definition of %s entered ...\n", tmepIDName.c_str() ) ;
              } // if 
              else 
                printf( "Definition of %s entered ...\n", tmepIDName.c_str() ) ;

              tempID.name = tmepIDName ;
              tempID.type = whichType ;
              tempID.constant = "" ;
              gIDList.push_back( tempID ) ;
              checkIndex ++ ;
              if ( gInput[checkIndex].name == "[" ) {
                checkIndex ++ ;
                if ( gInput[checkIndex].type == "Constant" ) {
                  gIDList[gIDList.size()-1].constant = gInput[checkIndex].name ;
                  checkIndex ++ ;
                  if ( gInput[checkIndex].name == "]" ) {
                    checkIndex ++ ;
                  } // if
                } // if
              } // if
              else if ( gInput[checkIndex].name == "," ) {
                int a = 0 ;
              } // else if 
              else if ( gInput[checkIndex].name == ";" ) {
                checkIndex ++ ;
                return true ;
              } // else if 
              
            } // if
          } // while
          
          if ( gInput[checkIndex].name == ";" ) {
            // May ERROR HERE !!!
            checkIndex++ ;
            return true ; 
          } // if 
        } // else if
      } // if 
    } // if 
  } // if 
  else if ( gInput[checkIndex].name == "," ) {
    while ( gInput[checkIndex].name == "," ) {
      checkIndex ++ ;
      if ( gInput[checkIndex].type == "identifier" ) {
        tmepIDName = gInput[checkIndex].name ;
        IDExistList = IDExist( gInput[checkIndex].name, IndexInIDList ) ;
        if ( IDExistList == true ) {
          gIDList.erase( gIDList.begin() + IndexInIDList ) ;
          printf( "New definition of %s entered ...\n", tmepIDName.c_str() ) ;
        } // if 
        else 
          printf( "Definition of %s entered ...\n", tmepIDName.c_str() ) ;

        tempID.name = tmepIDName ;
        tempID.type = whichType ;
        tempID.constant = "" ;
        gIDList.push_back( tempID ) ;
        checkIndex ++ ;
        if ( gInput[checkIndex].name == "[" ) {
          checkIndex ++ ;
          if ( gInput[checkIndex].type == "Constant" ) {
            gIDList[gIDList.size()-1].constant = gInput[checkIndex].name ;
            checkIndex ++ ;
            if ( gInput[checkIndex].name == "]" ) {
              checkIndex ++ ;
            } // if
          } // if
        } // if
        else if ( gInput[checkIndex].name == "," ) {
          int a = 0 ;
        } // else if 
        else if ( gInput[checkIndex].name == ";" ) {
          checkIndex ++ ;
          return true ;
        } // else if 
        
      } // if
    } // while
    
    if ( gInput[checkIndex].name == ";" ) {
      // May ERROR Here !!!
      checkIndex ++ ;
      return true ;
    } // if
  } // else if 
  else if ( gInput[checkIndex].name == ";" ) {
    checkIndex ++ ;
    // printf("CC") ;
    return true ;
  } // else if 
  else {
    return false ;
  } // else 
    
  return false ;
    
} // DoAgainRestOfDeclarators()

bool DoFunctionDefinitionWithoutID( int &checkIndex ) {
  if ( gInput[checkIndex].name == "(" ) {
    checkIndex ++ ;
    if ( gInput[checkIndex].name == ")" ) {
      checkIndex ++ ;
      if ( DoCompoundStaement( checkIndex ) == true )
        return true ;
      else 
        UnexpectedThrow( checkIndex ) ;
    } // if 
    else if ( gInput[checkIndex].type == "void" ) {
      checkIndex ++ ;
      if ( gInput[checkIndex].name == ")" ) {
        checkIndex ++ ;
        if ( DoCompoundStaement( checkIndex ) == true )
          return true ;
        else 
          UnexpectedThrow( checkIndex ) ;
      } // if 
      else 
        UnexpectedThrow( checkIndex ) ;
    } // else if
    else if ( DoFormalParameterList( checkIndex ) == true ) {
      // checkIndex ++ ;
      if ( gInput[checkIndex].name == ")" ) {
        checkIndex ++ ;
        if ( DoCompoundStaement( checkIndex ) == true )
          return true ;
        else 
          UnexpectedThrow( checkIndex ) ;
      } // if 
      else 
        UnexpectedThrow( checkIndex ) ;
    } // else if
    else {
      UnexpectedThrow( checkIndex ) ;
    } // else 
  } // if 
  else {
    return false ;
  } // else 
  
  return false ;
  
} // DoFunctionDefinitionWithoutID()

bool DoFormalParameterList( int &checkIndex ) {
  // printf("IN") ;
  string whichType ;
  IDENTData temp ;
  temp.type = gInput[checkIndex].name ;
  if ( DoTypeSpecifier( checkIndex, whichType ) == true ) {
    if ( gInput[checkIndex].name == "&" ) 
      checkIndex ++ ;
    
    if ( gInput[checkIndex].type == "identifier" ) {
      temp.name = gInput[checkIndex].name ;
      gIDTemp.push_back( temp ) ;
      checkIndex ++ ;
      if ( gInput[checkIndex].name == "[" ) {
        checkIndex ++ ;
        if ( gInput[checkIndex].type == "Constant" ) {
          checkIndex ++ ;
          if ( gInput[checkIndex].name == "]" ) {
            checkIndex ++ ;
            if ( gInput[checkIndex].name == "," ) {
              while ( gInput[checkIndex].name == "," ) {
                checkIndex ++ ;
                if ( DoTypeSpecifier( checkIndex, whichType ) == true ) {
                  if ( gInput[checkIndex].name == "&" ) 
                    checkIndex ++ ;
                  
                  if ( gInput[checkIndex].type == "identifier" ) {
                    temp.name = gInput[checkIndex].name ;
                    gIDTemp.push_back( temp ) ;
                    checkIndex ++ ;
                    if ( gInput[checkIndex].name == "[" ) {
                      checkIndex ++ ;
                      if ( gInput[checkIndex].type == "Constant" ) {
                        checkIndex ++ ;
                        if ( gInput[checkIndex].name == "]" ) {
                          checkIndex ++ ;
                        } // if 
                        else 
                          UnexpectedThrow( checkIndex ) ;
                      } // if 
                      else 
                        UnexpectedThrow( checkIndex ) ;
                    } // if 
                    else if ( gInput[checkIndex].name == "," ) {
                      int a = 0 ;
                    } // else if 
                    else {
                      return true ;
                    } // else
                  } // if 
                  else 
                    UnexpectedThrow( checkIndex ) ; 
                } // if 
                else 
                  UnexpectedThrow( checkIndex ) ;
                
              } // while 
            } // if 
            else 
              return true ;
          } // if
          else 
            UnexpectedThrow( checkIndex ) ;
        } // if 
        else 
          UnexpectedThrow( checkIndex ) ;
      } // if 
      else if ( gInput[checkIndex].name == "," ) {
        while ( gInput[checkIndex].name == "," ) {
          checkIndex ++ ;
          if ( DoTypeSpecifier( checkIndex, whichType ) == true ) {
            if ( gInput[checkIndex].name == "&" ) 
              checkIndex ++ ;
            
            if ( gInput[checkIndex].type == "identifier" ) {
              temp.name = gInput[checkIndex].name ;
              gIDTemp.push_back( temp ) ;
              checkIndex ++ ;
              if ( gInput[checkIndex].name == "[" ) {
                checkIndex ++ ;
                if ( gInput[checkIndex].type == "Constant" ) {
                  checkIndex ++ ;
                  if ( gInput[checkIndex].name == "]" ) {
                    checkIndex ++ ;
                  } // if 
                  else 
                    UnexpectedThrow( checkIndex ) ;
                } // if 
                else 
                  UnexpectedThrow( checkIndex ) ;
              } // if 
              else if ( gInput[checkIndex].name == "," ) {
                int a = 0 ;
              } // else if 
              else {
                return true ;
              } // else
            } // if 
            else 
              UnexpectedThrow( checkIndex ) ;              
          } // if 
          else 
            UnexpectedThrow( checkIndex ) ;
        } // while 
        
      } // else if 
      else 
        return true ;
    } // if 
    else 
      UnexpectedThrow( checkIndex ) ; // return false 
  } // if
  else {
    return false ;
  } // else 
    
  return false ;
  
} // DoFormalParameterList()

bool DoCompoundStaement( int &checkIndex ) {
  // printf("++") ;
  if ( gInput[checkIndex].name == "{" ) {
    checkIndex ++ ;
    if ( gInput[checkIndex].name == "}" ) {
      checkIndex ++ ;
      return true ;
    } // if 
    else if ( DoDeclaration( checkIndex ) == true || DoStatement( checkIndex ) == true ) {
      
      while ( DoDeclaration( checkIndex ) == true || DoStatement( checkIndex ) == true ) {
        int a = 0 ;
      } // while 
      
      if ( gInput[checkIndex].name == "}" ) {
        checkIndex ++ ;
        return true ;
      } // if
      else 
        UnexpectedThrow( checkIndex ) ;
      
    } // else if 
    else 
      UnexpectedThrow( checkIndex ) ;
  } // if
  else {
    return false ;
  } // else 
  
  return false ;
  
} // DoCompoundStaement()

bool DoDeclaration( int &checkIndex ) {
  string whichType ;
  IDENTData temp ;
  temp.type = gInput[checkIndex].name ;
  if ( DoTypeSpecifier( checkIndex, whichType ) == true ) {
    if ( gInput[checkIndex].type == "identifier" ) {
      temp.name = gInput[checkIndex].name ;
      gIDTemp.push_back( temp ) ;
      checkIndex ++ ;
      if ( DoRestOfDeclarators( checkIndex ) == true )
        return true ;
      else 
        UnexpectedThrow( checkIndex ) ;
    } // if  
    else 
      UnexpectedThrow( checkIndex ) ;
  } // if 
  else {
    return false ;
  } // else 
    
  return false ;
  
} // DoDeclaration()

bool DoStatement( int &checkIndex ) {
  bool realQuit ;
  if ( gInput[checkIndex].name == ";" ) {
    checkIndex ++ ;
    return true ;
  } // if 
  else if ( gInput[checkIndex].name == "return" ) {
    checkIndex ++ ;
    if ( Expression( checkIndex, realQuit ) == true ) {
      if ( gInput[checkIndex].name == ";" ) {
        checkIndex ++ ;
        return true ;
      } // if 
      else 
        UnexpectedThrow( checkIndex ) ;
    } // if 
    else if ( gInput[checkIndex].name == ";" ) {
      checkIndex ++ ;
      return true ;
    } // else if 
    else 
      UnexpectedThrow( checkIndex ) ;
  } // else if 
  else if ( gInput[checkIndex].name == "if" ) {
    checkIndex ++ ;
    if ( gInput[checkIndex].name == "(" ) {
      checkIndex ++ ;
      if ( Expression( checkIndex, realQuit ) == true ) {
        if ( gInput[checkIndex].name == ")" ) {
          checkIndex ++ ;
          if ( Statement( checkIndex, realQuit ) == true ) {
            if ( gInput[checkIndex].name == "else" ) {
              checkIndex ++ ;
              if ( Statement( checkIndex, realQuit ) == true ) {
                return true ;
              } // if 
              else 
                UnexpectedThrow( checkIndex ) ;                
            } // if 
            else 
              return true ;
          } // if 
          else 
            UnexpectedThrow( checkIndex ) ;
        } // if 
        else 
          UnexpectedThrow( checkIndex ) ;
      } // if
      else 
        UnexpectedThrow( checkIndex ) ;
    } // if 
    else 
      UnexpectedThrow( checkIndex ) ;
  } // else if 
  else if ( gInput[checkIndex].name == "while" ) {
    checkIndex ++ ;
    if ( gInput[checkIndex].name == "(" ) {
      checkIndex ++ ;
      if ( Expression( checkIndex, realQuit ) == true ) {
        if ( gInput[checkIndex].name == ")" ) {
          checkIndex ++ ;
          if ( Statement( checkIndex, realQuit ) == true ) 
            return true ; 
          else 
            UnexpectedThrow( checkIndex ) ;
        } // if 
        else 
          UnexpectedThrow( checkIndex ) ;
      } // if
      else 
        UnexpectedThrow( checkIndex ) ;
    } // if 
    else 
      UnexpectedThrow( checkIndex ) ;
  } // else if 
  else if ( gInput[checkIndex].name == "do" ) {
    checkIndex ++ ;
    if ( Statement( checkIndex, realQuit ) == true ) {
      if ( gInput[checkIndex].name == "while" ) {
        checkIndex ++ ;
        if ( gInput[checkIndex].name == "(" ) {
          checkIndex ++ ;
          if ( Expression( checkIndex, realQuit ) == true ) {
            if ( gInput[checkIndex].name == ")" ) {
              checkIndex ++ ;
              if ( gInput[checkIndex].name == ";" ) {
                checkIndex ++ ;
                return true ;
              } // if
              else 
                UnexpectedThrow( checkIndex ) ;
            } // if 
            else 
              UnexpectedThrow( checkIndex ) ;
          } // if 
          else 
            UnexpectedThrow( checkIndex ) ;
        } // if 
        else 
          UnexpectedThrow( checkIndex ) ;
      } // if 
      else 
        UnexpectedThrow( checkIndex ) ;
    } // if 
    else 
      UnexpectedThrow( checkIndex ) ;
  } // else if 
  else if ( CompoundStaement( checkIndex, realQuit ) == true ) {
    return true ;
  } // else if 
  else if ( Expression( checkIndex, realQuit ) == true ) {
    if ( gInput[checkIndex].name == ";" ) {
      checkIndex ++ ;
      return true ;
    } // if
    else 
      UnexpectedThrow( checkIndex ) ;
  } // else if 
  else {
    return false ;
  } // else 
    
  return false ;
  
} // DoStatement()

/*
bool DoExpression( int &checkIndex ) {} // DoExpression()

bool DoBasicExpression( int &checkIndex ) {} // DoBasicExpression()

bool DoRestOfIdentifierStartedBasicExp( int &checkIndex ) {} // DoRestOfIdentifierStartedBasicExp()

bool DoRestOfPPMMIdentifierStartedBasicExp( int &checkIndex ) {} // DoRestOfPPMMIdentifierStartedBasicExp()

bool DoSign( int &checkIndex ) {} // DoSign()

bool DoActualParameterList ( int &checkIndex ) {} // DoActualParameterList()

bool DoAssignmentOperator( int &checkIndex ) {} // DoAssignmentOperator()

bool DoRomceAndRomloe( int &checkIndex ) {} // DoRomceAndRomloe()

bool DoRestOfMaybeLogicalOrExp( int &checkIndex ) {} // DoRestOfMaybeLogicalOrExp()

bool DoMaybeLogicalAndExp( int &checkIndex ) {} // DoMaybeLogicalAndExp()

bool DoRestOfMaybeLogicalAndExp( int &checkIndex ) {} // DoRestOfMaybeLogicalAndExp()

bool DoMaybeBitOrExp( int &checkIndex ) {} // DoMaybeBitOrExp()

bool DoRestOfMaybeBitOrExp( int &checkIndex ) {} // DoRestOfMaybeBitOrExp()

bool DoMaybeBitExOrExp( int &checkIndex ) {} // DoMaybeBitExOrExp()

bool DoRestOfMaybeBitExOrExp( int &checkIndex ) {} // DoRestOfMaybeBitExOrExp()

bool DoMaybeBitAndExp( int &checkIndex ) {} // DoMaybeBitAndExp()

bool DoRestOfMaybeBitAndExp( int &checkIndex ) {} // DoRestOfMaybeBitAndExp()

bool DoMaybeEqualityExp( int &checkIndex ) {} // DoMaybeEqualityExp()

bool DoRestOfMaybeEqualityExp( int &checkIndex ) {} // DoRestOfMaybeEqualityExp()

bool DoMaybeRelationalExp( int &checkIndex ) {} // DoMaybeRelationalExp()

bool DoRestOfMaybeRelationalExp( int &checkIndex ) {} // DoRestOfMaybeRelationalExp()

bool DoMaybeShiftExp( int &checkIndex ) {} // DoMaybeShiftExp()

bool DoRestOfMaybeShiftExp( int &checkIndex ) {} // DoRestOfMaybeShiftExp()

bool DoMaybeAdditiveExp( int &checkIndex ) {} // DoMaybeAdditiveExp()

bool DoRestOfMaybeAdditiveExp( int &checkIndex ) {} // DoRestOfMaybeAdditiveExp()

bool DoMaybeMultExp( int &checkIndex ) {} // DoMaybeMultExp()

bool DoRestOfMaybeMultExp( int &checkIndex ) {} // DoRestOfMaybeMultExp()

bool DoUnaryExp( int &checkIndex ) {} // DoUnaryExp()

bool DoSignedUnaryExp( int &checkIndex ) {} // DoSignedUnaryExp()

bool DoUnsignedUnaryExp( int &checkIndex ) {} // DoUnsignedUnaryExp()
*/

// ------------------------------------------------------------------

void SkipToNextLine( int &checkIndex ) {
  // printf("%s",gInput[checkIndex].name) ;
  while ( checkIndex < gInput.size()-1 && gInput[checkIndex].whereLine == gInput[checkIndex+1].whereLine ) 
    checkIndex ++ ; 
    
  gInputHead = checkIndex ;
  checkIndex ++ ;
  // printf("%s",gInput[checkIndex].name) ;
  // printf( "%d %d",checkIndex,gInputHead ) ;
} // SkipToNextLine()

bool CheckGrmmar( int &checkIndex, bool &realQuit ) {
  try {
    if ( checkIndex < gInput.size() && UserInput( checkIndex, realQuit ) == true ) 
      return true ;
    else 
      return false ;
  } // try
  catch( string &error ) {
    printf( "%s'\n", error.c_str() ) ;
    gIDTemp.clear() ;
    SkipToNextLine( checkIndex ) ;
    // printf( "*%d %d*" ,checkIndex,gInputHead  ) ;
    return false ;
  } // catch
  
} // CheckGrmmar()

void Parser( char &uTestNum ) {
  // printf("\n\nParser") ;
  
  int checkIndex = 0 ; 
  checkIndex = checkIndex + 1 ;
  bool realQuit = false ;
  bool quitPrint = false ;
  while ( checkIndex < gInput.size() && realQuit == false ) {
    // printf( "%d", checkIndex ) ;
    if ( CheckGrmmar( checkIndex, realQuit ) == true && realQuit == false ) {
      // printf("&&") ;
      gIDTemp.clear() ;
    } // if 
    else if ( realQuit == true ) {
      printf( "> Our-C exited ..." ) ;
      quitPrint = true ;
    } // else if 

    // printf( "%d", checkIndex ) ;
  } // while

  if ( quitPrint == false ) {
    printf( "> Our-C exited ..." ) ;
    quitPrint = true ;
  } // if 
  
} // Parser()


int main() {
  printf( "Our-C running ...\n" ) ;
  char uTestNum ;
  Scaner( uTestNum ) ;
  // PrintInput() ; 
  Parser( uTestNum ) ;
}  // main()
