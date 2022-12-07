#pragma once

// https://github.com/dotnet/runtime/blob/v7.0.0/src/mono/wasi/mono-wasi-driver/driver.c
#include <mono-wasi/driver.h>
#include <stdint.h>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>

int native_power(int number) {
	return managed_multiply(number, number);
}

MonoMethod* method_Multiply;
int managed_multiply(int num1, int num2) {
	if (!method_Multiply)
	{
		method_Multiply = lookup_dotnet_method("WasiApp.dll", "WasiApp", "Native", "Multiply", -1);
		assert(method_Multiply);
	}

	void* method_params[] = { &num1, &num2 };
	MonoObject* exception;
	MonoObject* boxed_result = mono_wasm_invoke_method(method_Multiply, NULL, method_params, &exception);
	assert(!exception);

	//return 5532;
	int result = *(int*)mono_object_unbox(boxed_result);
	return result;
}

void attach_internal_calls()
{
	mono_add_internal_call("WasiApp.Native::Power", native_power);
}