// generated by Fast Light User Interface Designer (fluid) version 1.0500

#ifndef Grid_Tab_h
#define Grid_Tab_h
#include <FL/Fl.H>
#include "widgets/Formula_Input.h"
#include <FL/Fl_Group.H>
extern void propagate_load(Fl_Group*, void*);
#include <FL/Fl_Button.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Value_Input.H>

class Grid_Tab : public Fl_Group {
public:
  Grid_Tab(int X, int Y, int W, int H, const char *L = 0);
  fld::widget::Formula_Input *widget_grid_rows;
private:
  inline void cb_widget_grid_rows_i(fld::widget::Formula_Input*, void*);
  static void cb_widget_grid_rows(fld::widget::Formula_Input*, void*);
  inline void cb__i(Fl_Button*, void*);
  static void cb_(Fl_Button*, void*);
  inline void cb_1_i(Fl_Button*, void*);
  static void cb_1(Fl_Button*, void*);
public:
  fld::widget::Formula_Input *widget_grid_cols;
private:
  inline void cb_widget_grid_cols_i(fld::widget::Formula_Input*, void*);
  static void cb_widget_grid_cols(fld::widget::Formula_Input*, void*);
  inline void cb_2_i(Fl_Button*, void*);
  static void cb_2(Fl_Button*, void*);
  inline void cb_3_i(Fl_Button*, void*);
  static void cb_3(Fl_Button*, void*);
public:
  Fl_Group *wp_grid_margin;
private:
  inline void cb_Left_i(Fl_Value_Input*, void*);
  static void cb_Left(Fl_Value_Input*, void*);
  inline void cb_Top_i(Fl_Value_Input*, void*);
  static void cb_Top(Fl_Value_Input*, void*);
  inline void cb_Right_i(Fl_Value_Input*, void*);
  static void cb_Right(Fl_Value_Input*, void*);
  inline void cb_Bottom_i(Fl_Value_Input*, void*);
  static void cb_Bottom(Fl_Value_Input*, void*);
public:
  Fl_Group *wp_grid_gaps;
private:
  inline void cb_Row_i(Fl_Value_Input*, void*);
  static void cb_Row(Fl_Value_Input*, void*);
  inline void cb_Col_i(Fl_Value_Input*, void*);
  static void cb_Col(Fl_Value_Input*, void*);
  inline void cb_Row1_i(Fl_Group*, void*);
  static void cb_Row1(Fl_Group*, void*);
public:
  fld::widget::Formula_Input *widget_grid_curr_row;
private:
  inline void cb_widget_grid_curr_row_i(fld::widget::Formula_Input*, void*);
  static void cb_widget_grid_curr_row(fld::widget::Formula_Input*, void*);
  inline void cb_4_i(Fl_Button*, void*);
  static void cb_4(Fl_Button*, void*);
  inline void cb_5_i(Fl_Button*, void*);
  static void cb_5(Fl_Button*, void*);
public:
  Fl_Group *widget_grid_curr_row_attributes;
private:
  inline void cb_Height_i(fld::widget::Formula_Input*, void*);
  static void cb_Height(fld::widget::Formula_Input*, void*);
  inline void cb_Weight_i(fld::widget::Formula_Input*, void*);
  static void cb_Weight(fld::widget::Formula_Input*, void*);
  inline void cb_Gap_i(fld::widget::Formula_Input*, void*);
  static void cb_Gap(fld::widget::Formula_Input*, void*);
public:
  fld::widget::Formula_Input *widget_grid_curr_col;
private:
  inline void cb_widget_grid_curr_col_i(fld::widget::Formula_Input*, void*);
  static void cb_widget_grid_curr_col(fld::widget::Formula_Input*, void*);
  inline void cb_6_i(Fl_Button*, void*);
  static void cb_6(Fl_Button*, void*);
  inline void cb_7_i(Fl_Button*, void*);
  static void cb_7(Fl_Button*, void*);
public:
  Fl_Group *widget_grid_curr_col_attributes;
private:
  inline void cb_Width_i(fld::widget::Formula_Input*, void*);
  static void cb_Width(fld::widget::Formula_Input*, void*);
  inline void cb_Weight1_i(fld::widget::Formula_Input*, void*);
  static void cb_Weight1(fld::widget::Formula_Input*, void*);
  inline void cb_Gap1_i(fld::widget::Formula_Input*, void*);
  static void cb_Gap1(fld::widget::Formula_Input*, void*);
};
#endif
