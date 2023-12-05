#pragma once

/*
Ora definisco un FUNCTOR, vedi slide 45, per immagazzinare una funzione: la funzione la scrivo nel return, tramite l'overload dell'operatore()
quindi per ogni funzione che voglio usare scrivo un functor. In pratica è come se "potessi creare più funzioni" dello stesso tipo.  
*/
struct square
{
  double operator() (float t) {return t*t;}; 
};