#ifndef PERSONA_H
#define PERSONA_H

#include <string>

class Persona
{
    public:
        Persona();
        ~Persona();
        void setNombre(std::string nombre);
        std::string getNombre();
        void setRecord(int record);
        int getRecord();

    protected:

    private:
        std::string nombre = "";
        int record = 0;

};

#endif // PERSONA_H
