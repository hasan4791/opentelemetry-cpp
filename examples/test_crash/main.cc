#include "opentelemetry/trace/provider.h"
#include "opentelemetry/sdk/trace/batch_span_processor.h"
#include "opentelemetry/sdk/trace/tracer_provider.h"
#include "opentelemetry/exporters/jaeger/jaeger_exporter.h"


int main() {
	opentelemetry::nostd::string_view service_name="osd";
	opentelemetry::nostd::shared_ptr<opentelemetry::trace::Tracer> tracer;
	opentelemetry::exporter::jaeger::JaegerExporterOptions exporter_options;
	exporter_options.server_port = 9876;
	const opentelemetry::sdk::trace::BatchSpanProcessorOptions processor_options;
	const auto jaeger_resource = opentelemetry::sdk::resource::Resource::Create(std::move(opentelemetry::sdk::resource::ResourceAttributes{{"service.name", service_name}}));
	auto jaeger_exporter = std::unique_ptr<opentelemetry::sdk::trace::SpanExporter>(new opentelemetry::exporter::jaeger::JaegerExporter(exporter_options));
	auto processor = std::unique_ptr<opentelemetry::sdk::trace::SpanProcessor>(new opentelemetry::sdk::trace::BatchSpanProcessor(std::move(jaeger_exporter), processor_options));
	const auto provider = opentelemetry::nostd::shared_ptr<opentelemetry::trace::TracerProvider>(new opentelemetry::sdk::trace::TracerProvider(std::move(processor), jaeger_resource));
	opentelemetry::trace::Provider::SetTracerProvider(provider);
	tracer = provider->GetTracer(service_name, OPENTELEMETRY_SDK_VERSION);
	return 0;
}
