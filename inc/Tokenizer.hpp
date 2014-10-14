/**************************************************************************
 *  Copyright S. V. Paulauskas 2014                                       *
 *                                                                        *
 *  This program is free software: you can redistribute it and/or modify  *
 *  it under the terms of the GNU General Public License as published by  *
 *  the Free Software Foundation, version 3.0 License.                    *
 *                                                                        *
 *  This program is distributed in the hope that it will be useful,       *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *  GNU General Public License for more details.                          *
 *                                                                        *
 *  You should have received a copy of the GNU General Public License     *
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>. *
 *************************************************************************/
/*! \file Tokenizer.hpp
 *  \brief A class to tokenize a string
 *  \author S. V. Paulauskas
 *  \date  14 October 2014
 */
#ifndef __TOKENIZER_HPP__
#define __TOKENIZER_HPP__
#include <string>
#include <vector>

class Tokenizer {
public:
    //! Default Constructor
    Tokenizer(){};
    //! Default Destructor
    ~Tokenizer(){};

    /*! Constructor taking the delimiter and file to read
    *   \param[in] file: Name of the file to be read in and tokenized
    *   \param[in] delim: Delimiter in the file that we should look for
    */
    Tokenizer(const std::string &file, const std::string &delim);

    /*! \return Returns the X values of the tokenized file */
    std::vector<double> GetXVals(void) {return(xVals_);};
    /*! \return Returns the Y values of the tokenized file */
    std::vector<double> GetYVals(void){return(yVals_);};
    /*! \return Returns the Y error values of the tokenized file */
    std::vector<double> GetYErrorVals(void){return(yErrVals_);};

    /*! Set the delimiter that we will tokenize on*/
    void SetDelimiter(const std::string &a){delimiter_ = a;};
private:
    std::string delimiter_, file_;
    std::vector<double> xVals_, yVals_, yErrVals_;

    void Tokenize();
};
#endif // __TOKENIZER_HPP__
