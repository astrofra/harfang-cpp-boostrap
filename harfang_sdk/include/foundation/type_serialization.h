// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "foundation/binary_document.h"
#include "foundation/log.h"
#include "foundation/binary_blob.h"
#include "foundation/json_document.h"
#include "foundation/type_to_document.h"
#include "foundation/xml_document.h"

namespace gs {

IDocumentReader *NewResourceDocumentReader(const std::string &path, DocumentFormat format = DocumentFormatUnknown);
IDocumentWriter *NewResourceDocumentWriter(const std::string &path, DocumentFormat format);

IDocumentReader *DocumentReaderFromPath(const char *path, DocumentFormat format = DocumentFormatUnknown);
IDocumentReader *DocumentReaderFromString(const char *document, DocumentFormat format = DocumentFormatUnknown);

//----
struct SerializedObject {
	BinaryBlob data;
	size_t GetSize() const { return data.GetDataSize(); }
	bool Save(const char *path) const;
};

/// Deserialize a resource object from an object.
template <class T> bool LoadResourceFromObject(SerializedObject *object, T &o, DeserializationContext *ctx = nullptr) {
	BinaryDocumentReader doc;
	if (!object || !doc.Load(object->data))
		return false;
	return Deserialize(doc, &o, g_type_registry.get().GetType<T>(), ctx, nullptr);
}

/// Serialize a resource object to disk.
template <class T> SerializedObject *SaveResourceToObject(const T &o, SerializationContext *ctx = nullptr) {
	BinaryDocumentWriter doc;
	if (!Serialize(doc, &o, g_type_registry.get().GetType<T>(), ctx, nullptr))
		return nullptr;
	std::unique_ptr<SerializedObject> object(new SerializedObject);
	return doc.Save(object->data) ? object.release() : nullptr;
}

//----
/// Deserialize a resource object from disk.
template <class T> bool LoadResourceFromPath(const char *path, T &o, DocumentFormat format = DocumentFormatUnknown, DeserializationContext *ctx = nullptr) {
	std::unique_ptr<IDocumentReader> doc(DocumentReaderFromPath(path, format));
	return doc ? Deserialize(*doc, &o, g_type_registry.get().GetType<T>(), ctx, nullptr) : false;
}

/// Serialize a resource object to disk.
template <class T> bool SaveResourceToPath(const char *path, const T &o, DocumentFormat format = DocumentFormatUnknown, SerializationContext *ctx = nullptr) {
	std::unique_ptr<IDocumentWriter> doc(NewResourceDocumentWriter(path, format));
	return doc && Serialize(*doc, &o, g_type_registry.get().GetType<T>(), ctx, nullptr) && doc->Save(path);
}

//----
/// Deserialize a resource object from a string.
template <class T> bool LoadResourceFromString(const char *document, T &o, DocumentFormat format = DocumentFormatUnknown, DeserializationContext *ctx = nullptr) {
	std::unique_ptr<IDocumentReader> doc(DocumentReaderFromString(document));
	return doc ? Deserialize(*doc, &o, g_type_registry.get().GetType<T>(), ctx, nullptr) : false;
}

/// Serialize a resource object to a string.
template <class T> bool SaveResourceToString(std::string &out, const T &o, DocumentFormat format, SerializationContext *ctx = nullptr) {
	switch (format) {
		default:
			break;

		case DocumentFormatJSON: {
			JSONDocumentWriter doc;
			if (!Serialize(doc, &o, g_type_registry.get().GetType<T>(), ctx, nullptr))
				return false;
			out = doc.ToString();
		}
			return true;

		case DocumentFormatXML: {
			XMLDocumentWriter doc;
			if (!Serialize(doc, &o, g_type_registry.get().GetType<T>(), ctx, nullptr))
				return false;
			out = doc.ToString();
		}
			return true;
	}
	return false;
}

} // gs
