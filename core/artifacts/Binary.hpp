#pragma once

namespace Core { 
    class Binary {
    protected:
        bool enabled = false;
    public:
        virtual bool isEnabled();

        virtual void setEnabled(bool enabled);

        void toggle();

        void turnOff();

        void turnOn();

        virtual String toString();
    };

    bool Binary::isEnabled() {
        return enabled;
    }

    void Binary::toggle() {
        setEnabled(!isEnabled());
    }

    void Binary::turnOff() {
        setEnabled(false);
    }

    void Binary::turnOn() {
        setEnabled(true);
    }
}