#ifndef RESULT_H
#define RESULT_H

template <typename T, typename E>
class Result {
    public:
        void setError(const E& error) {
            ok = false;
            this->error = error;
        }
        E getError() const {
            return this->error;
        }
        void setValue(const T& value) {
            this->value = value;
        }
        T getValue() const {
            return this->value;
        }
        bool isOk() {
            return this->ok;
        }

    private:
        T value;
        E error;
        bool ok = true;
};
#endif