#pragma once
#ifndef STAR_PYTHON_HPP
#define STAR_PYTHON_HPP

#include <Python.h>

#include <exception>
#include <filesystem>
#include <functional>

namespace star::interop {
    class python {
    public:
        inline python() {
            Py_Initialize();
            this->check_initialized();
        }

        explicit inline python(PyConfig &config) {
            // 支持自定义config
            this->config = config;
            Py_InitializeFromConfig(&this->config);
            this->check_initialized();
        }

        template<typename ...Paths>
        inline explicit python(const char *python_home, const Paths ...paths) {
            /*
             * paths:
             *   python home         -> config.home                 -- python installation directory
             *   python dlls         -> config.module_search_paths  -- import packages need
             *   python lib          -> config.module_search_paths  -- import packages need
             *   module search path  -> config.module_search_paths  -- import your own packages
             */

            PyConfig_InitPythonConfig(&this->config);
            this->config.home = Py_DecodeLocale(python_home, nullptr);
            if constexpr (sizeof...(paths) > 0) {
                this->config.module_search_paths_set = 1;
            }
            auto set_paths = [this](auto &path) {
                PyWideStringList_Append(&this->config.module_search_paths, Py_DecodeLocale(path, nullptr));
            };
            (set_paths(paths), ...);
            Py_InitializeFromConfig(&this->config);
            this->check_initialized();
        }

        class object {
        public:
            object() = default;

            object(PyObject *obj) noexcept { // NOLINT(google-explicit-constructor)
                this->py_object = obj;
            }

            object &operator=(PyObject *obj) noexcept {
                this->py_object = obj;
                return *this;
            }

            PyObject *operator*() noexcept {
                return this->py_object;
            }

            PyObject *get() noexcept {
                return this->py_object;
            }

            ~object() {
                Py_XDECREF(this->py_object);
            }

        private:
            PyObject *py_object{};
        };

        std::function<bool()> is_initialized = Py_IsInitialized;

        std::function<PyObject * (PyObject * py_module, const char *attr_name
        )>
        get_attr_string = PyObject_GetAttrString;

        inline bool is_tuple(PyObject *obj) { // NOLINT(readability-convert-member-functions-to-static)
            return PyTuple_Check(obj);
        }

        inline auto get_tuple_size(PyObject *tuple) { // NOLINT(readability-convert-member-functions-to-static)
            return PyTuple_Size(tuple);
        }

        template<typename ...Args>
        inline PyObject *build_value(const char *format, Args ...args) {
            return Py_BuildValue(format, args...);
        }

        inline bool execute(const char *str) { // NOLINT(readability-convert-member-functions-to-static)
            // 执行单独python代码
            int result = PyRun_SimpleString(str);
            return result == 0;
        }

        inline void
        run_simple_file(const std::filesystem::path &path) { // NOLINT(readability-convert-member-functions-to-static)
            if (!exists(path)) {
                throw std::exception("run file path does not exist");
            }

            std::unique_ptr<FILE, std::function<void(FILE *)> > ptr(fopen(path.string().c_str(), "r"),
                                                                    [](FILE *f) { fclose(f); });
            PyRun_SimpleFile(ptr.get(), path.filename().string().c_str());
        }

        std::function< const char *(PyObject *)> get_utf8_from_PyUnicode = PyUnicode_AsUTF8;
        std::function<PyObject *(const char *)> get_PyUnicode_from_string = PyUnicode_FromString;

        std::function<PyObject *(const char *)> import_module = PyImport_ImportModule;

        template<typename ...Args>
        inline PyObject *call_function(PyObject *func, const char *format = nullptr, Args ...args) {
            return PyObject_CallFunction(func, format, args...);
        }

        inline PyObject *call_object(PyObject *py_object, // NOLINT(readability-convert-member-functions-to-static)
                                     PyObject *py_args = nullptr) {
            return PyObject_CallObject(py_object, py_args);
        }

        template<typename ...Args>
        inline PyObject *
        call_method(PyObject *object, const char *method_name, const char *format = nullptr, Args ...args) {
            return PyObject_CallMethod(object, method_name, format, args...);
        }

        template<typename ...Args>
        inline void reduce_reference_count(Args ...args) { // NOLINT(readability-convert-member-functions-to-static)
            auto reduce = [](auto &arg) {
                Py_XDECREF(arg);
            };
            (reduce(args), ...);
        }

        std::function<void(void)> print_error = PyErr_Print;

        ~python() {
            PyConfig_Clear(&this->config);
            Py_Finalize();
        }

    protected:
        inline void check_initialized() { // NOLINT(readability-convert-member-functions-to-static)
            if (!Py_IsInitialized()) {
                throw std::exception("Python initialize error");
            }
        }

    private:
        PyConfig config{};
    };
}


#endif //STAR_PYTHON_HPP

