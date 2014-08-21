// cust.h
// Loker, Nathaniel
// nloker
#ifndef CUST_H
#define CUST_H
#include<iostream>
#include<string>
using namespace std;

class Cust{
  public:
    Cust(string name, int arrival, int items, bool type);
    void print(ostream &os);
    void print_entered(ostream &os, int clock);
    void print_done_shopping(ostream &os, int clock);
    void print_started_checkout(ostream &os, int clock, int i);
    void print_checkout_shopper(ostream &os, int clock, int i);
    void print_checkout_robber(ostream &os, int clock, int i, int cash_in_reg);
    int arrival_time();
    int num_items();
    bool get_m_type();

  private:
    string m_name;
    int m_arrival;
    int m_items;
    bool m_type;

};
#endif



