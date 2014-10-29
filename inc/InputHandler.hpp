/*! \file
 *  \brief
 *
 *
 *  \author
 *  \date
*/#ifndef __INPUTHANDLER_HPP__
#define __INPUTHANDLER_HPP__


class InputHandler {
public:
    /** Default constructor */
    InputHandler();
    /** Default destructor */
    ~InputHandler(){};
    /** Access rangeLow_
    * \return The current value of rangeLow_
    */
    unsigned int GetRangeLow() { return rangeLow_; }
    /** Set rangeLow_
    * \param val New value to set
    */
    void SetRangeLow(unsigned int &val) { rangeLow_ = val; }
    /** Access rangeHigh_
    * \return The current value of rangeHigh_
    */
    unsigned int GetRangeHigh() { return rangeHigh_; }
    /** Set rangeHigh_
    * \param val New value to set
    */
    void SetRangeHigh(unsigned int &val) { rangeHigh_ = val; }
    /** Access funcNum_
    * \return The current value of funcNum_
    */
    unsigned int GetFuncNum() { return funcNum_; }
    /** Set funcNum_
    * \param val New value to set
    */
    void SetFuncNum(unsigned int &val) { funcNum_ = val; }
    /** Access doFitAgain_
    * \return The current value of doFitAgain_
    */
    bool GetDoFitAgain() { return doFitAgain_; }
    /** Set doFitAgain_
    * \param val New value to set
    */
    void SetDoFitAgain() { ReadRepeatFit(); }
private:
    void ReadFunctionNumber(void);
    void ReadFittingRange(void);
    void ReadRepeatFit(void);
    void RereadInput(unsigned int &inputNum);
    void OutputError(unsigned int &errNum);

    bool doFitAgain_;

    unsigned int rangeLow_; //!< Member variable "rangeLow_"
    unsigned int rangeHigh_; //!< Member variable "rangeHigh_"
    unsigned int funcNum_; //!< Member variable "funcNum_"
};
#endif // __INPUTHANDLER_HPP__
