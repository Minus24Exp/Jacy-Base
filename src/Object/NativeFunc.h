#ifndef NATIVEFUNC_H
#define NATIVEFUNC_H

#include <functional>
#include <unordered_map>
#include "object/Callable.h"

class NativeFunc;
using nf_ptr = std::unique_ptr<NativeFunc>;

using NFArgs = std::unordered_map<std::string, obj_ptr>;
using NFBody = std::function<obj_ptr(NFArgs&&)>;

class NativeFunc : public Callable {
public:
	NativeFunc(scope_ptr closure,
			   const std::string & name,
			   const Params & params,
			   const NFBody & body
			  ) : Callable(closure, name, params),
				  body(body) {}
	virtual ~NativeFunc() = default;

	// Object //
	obj_ptr clone() const override {
		// // As params contains unique_ptr of default values I need to create a copy of it
		// Params params_copy;
		// params_copy.reserve(params.size());
		// for(const auto & p : params){
		// 	params_copy.push_back(Param(p.name, p.default_val ? p.default_val->clone() : nullptr));
		// }
		return std::make_shared<NativeFunc>(closure, name, params, body);
	}

	std::string to_string() const override {
		return "<native_func:"+ name +">";
	}

	// Callable //
	obj_ptr call(Interpreter & interpreter, ObjList && args) override;

	obj_ptr bind(obj_ptr instance) override {
		scope_ptr scope = std::make_shared<Scope>(closure);
		scope->define("this", {LocalDeclType::Val, instance});
		return std::make_shared<NativeFunc>(scope, name, params, body);
	}

private:
	NFBody body;
};

static inline obj_ptr make_nf(scope_ptr closure,
							  const std::string & name,
							  const Params & params,
							  const NFBody & body)
{
	return std::make_shared<NativeFunc>(closure, name, params, body);
}

#endif