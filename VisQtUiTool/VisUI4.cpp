#include "VisUI4.h"

/*******************************************************************************
** Implementations
*/

void VisDomUI::clear(bool clear_all)
{
	delete m_widget;
	delete m_layoutDefault;
	delete m_layoutFunction;
	delete m_customWidgets;
	delete m_tabStops;
	delete m_images;
	delete m_includes;
	delete m_resources;
	delete m_connections;
	delete m_designerdata;
	delete m_slots;
	delete m_buttonGroups;

	if (clear_all) {
		m_text.clear();
		m_has_attr_version = false;
		m_has_attr_language = false;
		m_has_attr_displayname = false;
		m_has_attr_stdsetdef = false;
		m_attr_stdsetdef = 0;
		m_has_attr_stdSetDef = false;
		m_attr_stdSetDef = 0;
	}

	m_children = 0;
	m_widget = 0;
	m_layoutDefault = 0;
	m_layoutFunction = 0;
	m_customWidgets = 0;
	m_tabStops = 0;
	m_images = 0;
	m_includes = 0;
	m_resources = 0;
	m_connections = 0;
	m_designerdata = 0;
	m_slots = 0;
	m_buttonGroups = 0;
}

VisDomUI::VisDomUI()
{
	m_children = 0;
	m_has_attr_version = false;
	m_has_attr_language = false;
	m_has_attr_displayname = false;
	m_has_attr_stdsetdef = false;
	m_attr_stdsetdef = 0;
	m_has_attr_stdSetDef = false;
	m_attr_stdSetDef = 0;
	m_widget = 0;
	m_layoutDefault = 0;
	m_layoutFunction = 0;
	m_customWidgets = 0;
	m_tabStops = 0;
	m_images = 0;
	m_includes = 0;
	m_resources = 0;
	m_connections = 0;
	m_designerdata = 0;
	m_slots = 0;
	m_buttonGroups = 0;
}

VisDomUI::~VisDomUI()
{
	delete m_widget;
	delete m_layoutDefault;
	delete m_layoutFunction;
	delete m_customWidgets;
	delete m_tabStops;
	delete m_images;
	delete m_includes;
	delete m_resources;
	delete m_connections;
	delete m_designerdata;
	delete m_slots;
	delete m_buttonGroups;
}

void VisDomUI::read(QXmlStreamReader &reader)
{

	const QXmlStreamAttributes attributes = reader.attributes();
	
	//for (const QXmlStreamAttribute &attribute : attributes) {
	for (int i = 0; i < attributes.size(); i++) {
		const QXmlStreamAttribute &attribute = attributes.at(i);
		QStringRef name = attribute.name();
		if (name == QLatin1String("version")) {
			setAttributeVersion(attribute.value().toString());
			continue;
		}
		if (name == QLatin1String("language")) {
			setAttributeLanguage(attribute.value().toString());
			continue;
		}
		if (name == QLatin1String("displayname")) {
			setAttributeDisplayname(attribute.value().toString());
			continue;
		}
		if (name == QLatin1String("stdsetdef")) {
			setAttributeStdsetdef(attribute.value().toInt());
			continue;
		}
		if (name == QLatin1String("stdSetDef")) {
			setAttributeStdSetDef(attribute.value().toInt());
			continue;
		}
		reader.raiseError(QLatin1String("Unexpected attribute ")/* + name*/);
	}

	for (bool finished = false; !finished && !reader.hasError();) {
		switch (reader.readNext()) {
		case QXmlStreamReader::StartElement : {
			const QString tag = reader.name().toString().toLower();
			if (tag == QLatin1String("author")) {
				setElementAuthor(reader.readElementText());
				continue;
			}
			if (tag == QLatin1String("comment")) {
				setElementComment(reader.readElementText());
				continue;
			}
			if (tag == QLatin1String("exportmacro")) {
				setElementExportMacro(reader.readElementText());
				continue;
			}
			if (tag == QLatin1String("class")) {
				setElementClass(reader.readElementText());
				continue;
			}
			if (tag == QLatin1String("widget")) {
				VisDomWidget *v = new VisDomWidget();
				v->read(reader);
				setElementWidget(v);
				continue;
			}
			if (tag == QLatin1String("layoutdefault")) {
				VisDomLayoutDefault *v = new VisDomLayoutDefault();
				v->read(reader);
				setElementLayoutDefault(v);
				continue;
			}
			if (tag == QLatin1String("layoutfunction")) {
				VisDomLayoutFunction *v = new VisDomLayoutFunction();
				v->read(reader);
				setElementLayoutFunction(v);
				continue;
			}
			if (tag == QLatin1String("pixmapfunction")) {
				setElementPixmapFunction(reader.readElementText());
				continue;
			}
			if (tag == QLatin1String("customwidgets")) {
				VisDomCustomWidgets *v = new VisDomCustomWidgets();
				v->read(reader);
				setElementCustomWidgets(v);
				continue;
			}
			if (tag == QLatin1String("tabstops")) {
				VisDomTabStops *v = new VisDomTabStops();
				v->read(reader);
				setElementTabStops(v);
				continue;
			}
			if (tag == QLatin1String("images")) {
				VisDomImages *v = new VisDomImages();
				v->read(reader);
				setElementImages(v);
				continue;
			}
			if (tag == QLatin1String("includes")) {
				VisDomIncludes *v = new VisDomIncludes();
				v->read(reader);
				setElementIncludes(v);
				continue;
			}
			if (tag == QLatin1String("resources")) {
				VisDomResources *v = new VisDomResources();
				v->read(reader);
				setElementResources(v);
				continue;
			}
			if (tag == QLatin1String("connections")) {
				VisDomConnections *v = new VisDomConnections();
				v->read(reader);
				setElementConnections(v);
				continue;
			}
			if (tag == QLatin1String("designerdata")) {
				VisDomDesignerData *v = new VisDomDesignerData();
				v->read(reader);
				setElementDesignerdata(v);
				continue;
			}
			if (tag == QLatin1String("slots")) {
				VisDomSlots *v = new VisDomSlots();
				v->read(reader);
				setElementSlots(v);
				continue;
			}
			if (tag == QLatin1String("buttongroups")) {
				VisDomButtonGroups *v = new VisDomButtonGroups();
				v->read(reader);
				setElementButtonGroups(v);
				continue;
			}
			reader.raiseError(QLatin1String("Unexpected element ") + tag);
											  }
											  break;
		case QXmlStreamReader::EndElement :
			finished = true;
			break;
		case QXmlStreamReader::Characters :
			if (!reader.isWhitespace())
				m_text.append(reader.text().toString());
			break;
		default :
			break;
		}
	}
}

void VisDomUI::write(QXmlStreamWriter &writer, const QString &tagName) const
{
	writer.writeStartElement(tagName.isEmpty() ? QString::fromUtf8("ui") : tagName.toLower());

	if (hasAttributeVersion())
		writer.writeAttribute(QStringLiteral("version"), attributeVersion());

	if (hasAttributeLanguage())
		writer.writeAttribute(QStringLiteral("language"), attributeLanguage());

	if (hasAttributeDisplayname())
		writer.writeAttribute(QStringLiteral("displayname"), attributeDisplayname());

	if (hasAttributeStdsetdef())
		writer.writeAttribute(QStringLiteral("stdsetdef"), QString::number(attributeStdsetdef()));

	if (hasAttributeStdSetDef())
		writer.writeAttribute(QStringLiteral("stdsetdef"), QString::number(attributeStdSetDef()));

	if (m_children & Author) {
		writer.writeTextElement(QStringLiteral("author"), m_author);
	}

	if (m_children & Comment) {
		writer.writeTextElement(QStringLiteral("comment"), m_comment);
	}

	if (m_children & ExportMacro) {
		writer.writeTextElement(QStringLiteral("exportmacro"), m_exportMacro);
	}

	if (m_children & Class) {
		writer.writeTextElement(QStringLiteral("class"), m_class);
	}

	if (m_children & Widget) {
		m_widget->write(writer, QStringLiteral("widget"));
	}

	if (m_children & LayoutDefault) {
		m_layoutDefault->write(writer, QStringLiteral("layoutdefault"));
	}

	if (m_children & LayoutFunction) {
		m_layoutFunction->write(writer, QStringLiteral("layoutfunction"));
	}

	if (m_children & PixmapFunction) {
		writer.writeTextElement(QStringLiteral("pixmapfunction"), m_pixmapFunction);
	}

	if (m_children & CustomWidgets) {
		m_customWidgets->write(writer, QStringLiteral("customwidgets"));
	}

	if (m_children & TabStops) {
		m_tabStops->write(writer, QStringLiteral("tabstops"));
	}

	if (m_children & Images) {
		m_images->write(writer, QStringLiteral("images"));
	}

	if (m_children & Includes) {
		m_includes->write(writer, QStringLiteral("includes"));
	}

	if (m_children & Resources) {
		m_resources->write(writer, QStringLiteral("resources"));
	}

	if (m_children & Connections) {
		m_connections->write(writer, QStringLiteral("connections"));
	}

	if (m_children & Designerdata) {
		m_designerdata->write(writer, QStringLiteral("designerdata"));
	}

	if (m_children & Slots) {
		m_slots->write(writer, QStringLiteral("slots"));
	}

	if (m_children & ButtonGroups) {
		m_buttonGroups->write(writer, QStringLiteral("buttongroups"));
	}

	if (!m_text.isEmpty())
		writer.writeCharacters(m_text);

	writer.writeEndElement();
}

void VisDomUI::setElementAuthor(const QString& a)
{
	m_children |= Author;
	m_author = a;
}

void VisDomUI::setElementComment(const QString& a)
{
	m_children |= Comment;
	m_comment = a;
}

void VisDomUI::setElementExportMacro(const QString& a)
{
	m_children |= ExportMacro;
	m_exportMacro = a;
}

void VisDomUI::setElementClass(const QString& a)
{
	m_children |= Class;
	m_class = a;
}

VisDomWidget* VisDomUI::takeElementWidget()
{
	VisDomWidget* a = m_widget;
	m_widget = 0;
	m_children ^= Widget;
	return a;
}

void VisDomUI::setElementWidget(VisDomWidget* a)
{
	delete m_widget;
	m_children |= Widget;
	m_widget = a;
}

VisDomLayoutDefault* VisDomUI::takeElementLayoutDefault()
{
	VisDomLayoutDefault* a = m_layoutDefault;
	m_layoutDefault = 0;
	m_children ^= LayoutDefault;
	return a;
}

void VisDomUI::setElementLayoutDefault(VisDomLayoutDefault* a)
{
	delete m_layoutDefault;
	m_children |= LayoutDefault;
	m_layoutDefault = a;
}

VisDomLayoutFunction* VisDomUI::takeElementLayoutFunction()
{
	VisDomLayoutFunction* a = m_layoutFunction;
	m_layoutFunction = 0;
	m_children ^= LayoutFunction;
	return a;
}

void VisDomUI::setElementLayoutFunction(VisDomLayoutFunction* a)
{
	delete m_layoutFunction;
	m_children |= LayoutFunction;
	m_layoutFunction = a;
}

void VisDomUI::setElementPixmapFunction(const QString& a)
{
	m_children |= PixmapFunction;
	m_pixmapFunction = a;
}

VisDomCustomWidgets* VisDomUI::takeElementCustomWidgets()
{
	VisDomCustomWidgets* a = m_customWidgets;
	m_customWidgets = 0;
	m_children ^= CustomWidgets;
	return a;
}

void VisDomUI::setElementCustomWidgets(VisDomCustomWidgets* a)
{
	delete m_customWidgets;
	m_children |= CustomWidgets;
	m_customWidgets = a;
}

VisDomTabStops* VisDomUI::takeElementTabStops()
{
	VisDomTabStops* a = m_tabStops;
	m_tabStops = 0;
	m_children ^= TabStops;
	return a;
}

void VisDomUI::setElementTabStops(VisDomTabStops* a)
{
	delete m_tabStops;
	m_children |= TabStops;
	m_tabStops = a;
}

VisDomImages* VisDomUI::takeElementImages()
{
	VisDomImages* a = m_images;
	m_images = 0;
	m_children ^= Images;
	return a;
}

void VisDomUI::setElementImages(VisDomImages* a)
{
	delete m_images;
	m_children |= Images;
	m_images = a;
}

VisDomIncludes* VisDomUI::takeElementIncludes()
{
	VisDomIncludes* a = m_includes;
	m_includes = 0;
	m_children ^= Includes;
	return a;
}

void VisDomUI::setElementIncludes(VisDomIncludes* a)
{
	delete m_includes;
	m_children |= Includes;
	m_includes = a;
}

VisDomResources* VisDomUI::takeElementResources()
{
	VisDomResources* a = m_resources;
	m_resources = 0;
	m_children ^= Resources;
	return a;
}

void VisDomUI::setElementResources(VisDomResources* a)
{
	delete m_resources;
	m_children |= Resources;
	m_resources = a;
}

VisDomConnections* VisDomUI::takeElementConnections()
{
	VisDomConnections* a = m_connections;
	m_connections = 0;
	m_children ^= Connections;
	return a;
}

void VisDomUI::setElementConnections(VisDomConnections* a)
{
	delete m_connections;
	m_children |= Connections;
	m_connections = a;
}

VisDomDesignerData* VisDomUI::takeElementDesignerdata()
{
	VisDomDesignerData* a = m_designerdata;
	m_designerdata = 0;
	m_children ^= Designerdata;
	return a;
}

void VisDomUI::setElementDesignerdata(VisDomDesignerData* a)
{
	delete m_designerdata;
	m_children |= Designerdata;
	m_designerdata = a;
}

VisDomSlots* VisDomUI::takeElementSlots()
{
	VisDomSlots* a = m_slots;
	m_slots = 0;
	m_children ^= Slots;
	return a;
}

void VisDomUI::setElementSlots(VisDomSlots* a)
{
	delete m_slots;
	m_children |= Slots;
	m_slots = a;
}

VisDomButtonGroups* VisDomUI::takeElementButtonGroups()
{
	VisDomButtonGroups* a = m_buttonGroups;
	m_buttonGroups = 0;
	m_children ^= ButtonGroups;
	return a;
}

void VisDomUI::setElementButtonGroups(VisDomButtonGroups* a)
{
	delete m_buttonGroups;
	m_children |= ButtonGroups;
	m_buttonGroups = a;
}

void VisDomUI::clearElementAuthor()
{
	m_children &= ~Author;
}

void VisDomUI::clearElementComment()
{
	m_children &= ~Comment;
}

void VisDomUI::clearElementExportMacro()
{
	m_children &= ~ExportMacro;
}

void VisDomUI::clearElementClass()
{
	m_children &= ~Class;
}

void VisDomUI::clearElementWidget()
{
	delete m_widget;
	m_widget = 0;
	m_children &= ~Widget;
}

void VisDomUI::clearElementLayoutDefault()
{
	delete m_layoutDefault;
	m_layoutDefault = 0;
	m_children &= ~LayoutDefault;
}

void VisDomUI::clearElementLayoutFunction()
{
	delete m_layoutFunction;
	m_layoutFunction = 0;
	m_children &= ~LayoutFunction;
}

void VisDomUI::clearElementPixmapFunction()
{
	m_children &= ~PixmapFunction;
}

void VisDomUI::clearElementCustomWidgets()
{
	delete m_customWidgets;
	m_customWidgets = 0;
	m_children &= ~CustomWidgets;
}

void VisDomUI::clearElementTabStops()
{
	delete m_tabStops;
	m_tabStops = 0;
	m_children &= ~TabStops;
}

void VisDomUI::clearElementImages()
{
	delete m_images;
	m_images = 0;
	m_children &= ~Images;
}

void VisDomUI::clearElementIncludes()
{
	delete m_includes;
	m_includes = 0;
	m_children &= ~Includes;
}

void VisDomUI::clearElementResources()
{
	delete m_resources;
	m_resources = 0;
	m_children &= ~Resources;
}

void VisDomUI::clearElementConnections()
{
	delete m_connections;
	m_connections = 0;
	m_children &= ~Connections;
}

void VisDomUI::clearElementDesignerdata()
{
	delete m_designerdata;
	m_designerdata = 0;
	m_children &= ~Designerdata;
}

void VisDomUI::clearElementSlots()
{
	delete m_slots;
	m_slots = 0;
	m_children &= ~Slots;
}

void VisDomUI::clearElementButtonGroups()
{
	delete m_buttonGroups;
	m_buttonGroups = 0;
	m_children &= ~ButtonGroups;
}

void VisDomIncludes::clear(bool clear_all)
{
	qDeleteAll(m_include);
	m_include.clear();

	if (clear_all) {
		m_text.clear();
	}

	m_children = 0;
}

VisDomIncludes::VisDomIncludes()
{
	m_children = 0;
}

VisDomIncludes::~VisDomIncludes()
{
	qDeleteAll(m_include);
	m_include.clear();
}

void VisDomIncludes::read(QXmlStreamReader &reader)
{

	for (bool finished = false; !finished && !reader.hasError();) {
		switch (reader.readNext()) {
		case QXmlStreamReader::StartElement : {
			const QString tag = reader.name().toString().toLower();
			if (tag == QLatin1String("include")) {
				VisDomInclude *v = new VisDomInclude();
				v->read(reader);
				m_include.append(v);
				continue;
			}
			reader.raiseError(QLatin1String("Unexpected element ") + tag);
											  }
											  break;
		case QXmlStreamReader::EndElement :
			finished = true;
			break;
		case QXmlStreamReader::Characters :
			if (!reader.isWhitespace())
				m_text.append(reader.text().toString());
			break;
		default :
			break;
		}
	}
}

void VisDomIncludes::write(QXmlStreamWriter &writer, const QString &tagName) const
{
	writer.writeStartElement(tagName.isEmpty() ? QString::fromUtf8("includes") : tagName.toLower());

	for (int i = 0; i < m_include.size(); ++i) {
		VisDomInclude* v = m_include[i];
		v->write(writer, QStringLiteral("include"));
	}
	if (!m_text.isEmpty())
		writer.writeCharacters(m_text);

	writer.writeEndElement();
}

void VisDomIncludes::setElementInclude(const QList<VisDomInclude*>& a)
{
	m_children |= Include;
	m_include = a;
}

void VisDomInclude::clear(bool clear_all)
{

	if (clear_all) {
		m_text.clear();
		m_has_attr_location = false;
		m_has_attr_impldecl = false;
	}

	m_children = 0;
}

VisDomInclude::VisDomInclude()
{
	m_children = 0;
	m_has_attr_location = false;
	m_has_attr_impldecl = false;
	m_text.clear();
}

VisDomInclude::~VisDomInclude()
{
}

void VisDomInclude::read(QXmlStreamReader &reader)
{

	const QXmlStreamAttributes attributes = reader.attributes();
	//for (const QXmlStreamAttribute &attribute : attributes) {
	for (int i = 0; i < attributes.size(); i++) {
		const QXmlStreamAttribute &attribute = attributes.at(i);
		QStringRef name = attribute.name();
		if (name == QLatin1String("location")) {
			setAttributeLocation(attribute.value().toString());
			continue;
		}
		if (name == QLatin1String("impldecl")) {
			setAttributeImpldecl(attribute.value().toString());
			continue;
		}
		reader.raiseError(QLatin1String("Unexpected attribute ")/* + name*/);
	}

	for (bool finished = false; !finished && !reader.hasError();) {
		switch (reader.readNext()) {
		case QXmlStreamReader::StartElement : {
			const QString tag = reader.name().toString().toLower();
			reader.raiseError(QLatin1String("Unexpected element ") + tag);
											  }
											  break;
		case QXmlStreamReader::EndElement :
			finished = true;
			break;
		case QXmlStreamReader::Characters :
			if (!reader.isWhitespace())
				m_text.append(reader.text().toString());
			break;
		default :
			break;
		}
	}
}

void VisDomInclude::write(QXmlStreamWriter &writer, const QString &tagName) const
{
	writer.writeStartElement(tagName.isEmpty() ? QString::fromUtf8("include") : tagName.toLower());

	if (hasAttributeLocation())
		writer.writeAttribute(QStringLiteral("location"), attributeLocation());

	if (hasAttributeImpldecl())
		writer.writeAttribute(QStringLiteral("impldecl"), attributeImpldecl());

	if (!m_text.isEmpty())
		writer.writeCharacters(m_text);

	writer.writeEndElement();
}

void VisDomResources::clear(bool clear_all)
{
	qDeleteAll(m_include);
	m_include.clear();

	if (clear_all) {
		m_text.clear();
		m_has_attr_name = false;
	}

	m_children = 0;
}

VisDomResources::VisDomResources()
{
	m_children = 0;
	m_has_attr_name = false;
}

VisDomResources::~VisDomResources()
{
	qDeleteAll(m_include);
	m_include.clear();
}

void VisDomResources::read(QXmlStreamReader &reader)
{

	const QXmlStreamAttributes attributes = reader.attributes();
	//for (const QXmlStreamAttribute &attribute : attributes) {
	for (int i = 0; i < attributes.size(); i++) {
		const QXmlStreamAttribute &attribute = attributes.at(i);
		QStringRef name = attribute.name();
		if (name == QLatin1String("name")) {
			setAttributeName(attribute.value().toString());
			continue;
		}
		reader.raiseError(QLatin1String("Unexpected attribute ") /*+ name*/);
	}

	for (bool finished = false; !finished && !reader.hasError();) {
		switch (reader.readNext()) {
		case QXmlStreamReader::StartElement : {
			const QString tag = reader.name().toString().toLower();
			if (tag == QLatin1String("include")) {
				VisDomResource *v = new VisDomResource();
				v->read(reader);
				m_include.append(v);
				continue;
			}
			reader.raiseError(QLatin1String("Unexpected element ") + tag);
											  }
											  break;
		case QXmlStreamReader::EndElement :
			finished = true;
			break;
		case QXmlStreamReader::Characters :
			if (!reader.isWhitespace())
				m_text.append(reader.text().toString());
			break;
		default :
			break;
		}
	}
}

void VisDomResources::write(QXmlStreamWriter &writer, const QString &tagName) const
{
	writer.writeStartElement(tagName.isEmpty() ? QString::fromUtf8("resources") : tagName.toLower());

	if (hasAttributeName())
		writer.writeAttribute(QStringLiteral("name"), attributeName());

	for (int i = 0; i < m_include.size(); ++i) {
		VisDomResource* v = m_include[i];
		v->write(writer, QStringLiteral("include"));
	}
	if (!m_text.isEmpty())
		writer.writeCharacters(m_text);

	writer.writeEndElement();
}

void VisDomResources::setElementInclude(const QList<VisDomResource*>& a)
{
	m_children |= Include;
	m_include = a;
}

void VisDomResource::clear(bool clear_all)
{

	if (clear_all) {
		m_text.clear();
		m_has_attr_location = false;
	}

	m_children = 0;
}

VisDomResource::VisDomResource()
{
	m_children = 0;
	m_has_attr_location = false;
}

VisDomResource::~VisDomResource()
{
}

void VisDomResource::read(QXmlStreamReader &reader)
{

	const QXmlStreamAttributes attributes = reader.attributes();
	//for (const QXmlStreamAttribute &attribute : attributes) {
	for (int i = 0; i < attributes.size(); i++) {
		const QXmlStreamAttribute &attribute = attributes.at(i);
		QStringRef name = attribute.name();
		if (name == QLatin1String("location")) {
			setAttributeLocation(attribute.value().toString());
			continue;
		}
		reader.raiseError(QLatin1String("Unexpected attribute ")/* + name*/);
	}

	for (bool finished = false; !finished && !reader.hasError();) {
		switch (reader.readNext()) {
		case QXmlStreamReader::StartElement : {
			const QString tag = reader.name().toString().toLower();
			reader.raiseError(QLatin1String("Unexpected element ") + tag);
											  }
											  break;
		case QXmlStreamReader::EndElement :
			finished = true;
			break;
		case QXmlStreamReader::Characters :
			if (!reader.isWhitespace())
				m_text.append(reader.text().toString());
			break;
		default :
			break;
		}
	}
}

void VisDomResource::write(QXmlStreamWriter &writer, const QString &tagName) const
{
	writer.writeStartElement(tagName.isEmpty() ? QString::fromUtf8("resource") : tagName.toLower());

	if (hasAttributeLocation())
		writer.writeAttribute(QStringLiteral("location"), attributeLocation());

	if (!m_text.isEmpty())
		writer.writeCharacters(m_text);

	writer.writeEndElement();
}

void VisDomActionGroup::clear(bool clear_all)
{
	qDeleteAll(m_action);
	m_action.clear();
	qDeleteAll(m_actionGroup);
	m_actionGroup.clear();
	qDeleteAll(m_property);
	m_property.clear();
	qDeleteAll(m_attribute);
	m_attribute.clear();

	if (clear_all) {
		m_text.clear();
		m_has_attr_name = false;
	}

	m_children = 0;
}

VisDomActionGroup::VisDomActionGroup()
{
	m_children = 0;
	m_has_attr_name = false;
}

VisDomActionGroup::~VisDomActionGroup()
{
	qDeleteAll(m_action);
	m_action.clear();
	qDeleteAll(m_actionGroup);
	m_actionGroup.clear();
	qDeleteAll(m_property);
	m_property.clear();
	qDeleteAll(m_attribute);
	m_attribute.clear();
}

void VisDomActionGroup::read(QXmlStreamReader &reader)
{

	const QXmlStreamAttributes attributes = reader.attributes();
	//for (const QXmlStreamAttribute &attribute : attributes) {
	for (int i = 0; i < attributes.size(); i++) {
		const QXmlStreamAttribute &attribute = attributes.at(i);
		QStringRef name = attribute.name();
		if (name == QLatin1String("name")) {
			setAttributeName(attribute.value().toString());
			continue;
		}
		reader.raiseError(QLatin1String("Unexpected attribute ")/* + name*/);
	}

	for (bool finished = false; !finished && !reader.hasError();) {
		switch (reader.readNext()) {
		case QXmlStreamReader::StartElement : {
			const QString tag = reader.name().toString().toLower();
			if (tag == QLatin1String("action")) {
				VisDomAction *v = new VisDomAction();
				v->read(reader);
				m_action.append(v);
				continue;
			}
			if (tag == QLatin1String("actiongroup")) {
				VisDomActionGroup *v = new VisDomActionGroup();
				v->read(reader);
				m_actionGroup.append(v);
				continue;
			}
			if (tag == QLatin1String("property")) {
				VisDomProperty *v = new VisDomProperty();
				v->read(reader);
				m_property.append(v);
				continue;
			}
			if (tag == QLatin1String("attribute")) {
				VisDomProperty *v = new VisDomProperty();
				v->read(reader);
				m_attribute.append(v);
				continue;
			}
			reader.raiseError(QLatin1String("Unexpected element ") + tag);
											  }
											  break;
		case QXmlStreamReader::EndElement :
			finished = true;
			break;
		case QXmlStreamReader::Characters :
			if (!reader.isWhitespace())
				m_text.append(reader.text().toString());
			break;
		default :
			break;
		}
	}
}

void VisDomActionGroup::write(QXmlStreamWriter &writer, const QString &tagName) const
{
	writer.writeStartElement(tagName.isEmpty() ? QString::fromUtf8("actiongroup") : tagName.toLower());

	if (hasAttributeName())
		writer.writeAttribute(QStringLiteral("name"), attributeName());

	for (int i = 0; i < m_action.size(); ++i) {
		VisDomAction* v = m_action[i];
		v->write(writer, QStringLiteral("action"));
	}
	for (int i = 0; i < m_actionGroup.size(); ++i) {
		VisDomActionGroup* v = m_actionGroup[i];
		v->write(writer, QStringLiteral("actiongroup"));
	}
	for (int i = 0; i < m_property.size(); ++i) {
		VisDomProperty* v = m_property[i];
		v->write(writer, QStringLiteral("property"));
	}
	for (int i = 0; i < m_attribute.size(); ++i) {
		VisDomProperty* v = m_attribute[i];
		v->write(writer, QStringLiteral("attribute"));
	}
	if (!m_text.isEmpty())
		writer.writeCharacters(m_text);

	writer.writeEndElement();
}

void VisDomActionGroup::setElementAction(const QList<VisDomAction*>& a)
{
	m_children |= Action;
	m_action = a;
}

void VisDomActionGroup::setElementActionGroup(const QList<VisDomActionGroup*>& a)
{
	m_children |= ActionGroup;
	m_actionGroup = a;
}

void VisDomActionGroup::setElementProperty(const QList<VisDomProperty*>& a)
{
	m_children |= Property;
	m_property = a;
}

void VisDomActionGroup::setElementAttribute(const QList<VisDomProperty*>& a)
{
	m_children |= Attribute;
	m_attribute = a;
}

void VisDomAction::clear(bool clear_all)
{
	qDeleteAll(m_property);
	m_property.clear();
	qDeleteAll(m_attribute);
	m_attribute.clear();

	if (clear_all) {
		m_text.clear();
		m_has_attr_name = false;
		m_has_attr_menu = false;
	}

	m_children = 0;
}

VisDomAction::VisDomAction()
{
	m_children = 0;
	m_has_attr_name = false;
	m_has_attr_menu = false;
}

VisDomAction::~VisDomAction()
{
	qDeleteAll(m_property);
	m_property.clear();
	qDeleteAll(m_attribute);
	m_attribute.clear();
}

void VisDomAction::read(QXmlStreamReader &reader)
{

	const QXmlStreamAttributes attributes = reader.attributes();
	//for (const QXmlStreamAttribute &attribute : attributes) {
	for (int i = 0; i < attributes.size(); i++) {
		const QXmlStreamAttribute &attribute = attributes.at(i);
		QStringRef name = attribute.name();
		if (name == QLatin1String("name")) {
			setAttributeName(attribute.value().toString());
			continue;
		}
		if (name == QLatin1String("menu")) {
			setAttributeMenu(attribute.value().toString());
			continue;
		}
		reader.raiseError(QLatin1String("Unexpected attribute ")/* + name*/);
	}

	for (bool finished = false; !finished && !reader.hasError();) {
		switch (reader.readNext()) {
		case QXmlStreamReader::StartElement : {
			const QString tag = reader.name().toString().toLower();
			if (tag == QLatin1String("property")) {
				VisDomProperty *v = new VisDomProperty();
				v->read(reader);
				m_property.append(v);
				continue;
			}
			if (tag == QLatin1String("attribute")) {
				VisDomProperty *v = new VisDomProperty();
				v->read(reader);
				m_attribute.append(v);
				continue;
			}
			reader.raiseError(QLatin1String("Unexpected element ") + tag);
											  }
											  break;
		case QXmlStreamReader::EndElement :
			finished = true;
			break;
		case QXmlStreamReader::Characters :
			if (!reader.isWhitespace())
				m_text.append(reader.text().toString());
			break;
		default :
			break;
		}
	}
}

void VisDomAction::write(QXmlStreamWriter &writer, const QString &tagName) const
{
	writer.writeStartElement(tagName.isEmpty() ? QString::fromUtf8("action") : tagName.toLower());

	if (hasAttributeName())
		writer.writeAttribute(QStringLiteral("name"), attributeName());

	if (hasAttributeMenu())
		writer.writeAttribute(QStringLiteral("menu"), attributeMenu());

	for (int i = 0; i < m_property.size(); ++i) {
		VisDomProperty* v = m_property[i];
		v->write(writer, QStringLiteral("property"));
	}
	for (int i = 0; i < m_attribute.size(); ++i) {
		VisDomProperty* v = m_attribute[i];
		v->write(writer, QStringLiteral("attribute"));
	}
	if (!m_text.isEmpty())
		writer.writeCharacters(m_text);

	writer.writeEndElement();
}

void VisDomAction::setElementProperty(const QList<VisDomProperty*>& a)
{
	m_children |= Property;
	m_property = a;
}

void VisDomAction::setElementAttribute(const QList<VisDomProperty*>& a)
{
	m_children |= Attribute;
	m_attribute = a;
}

void VisDomActionRef::clear(bool clear_all)
{

	if (clear_all) {
		m_text.clear();
		m_has_attr_name = false;
	}

	m_children = 0;
}

VisDomActionRef::VisDomActionRef()
{
	m_children = 0;
	m_has_attr_name = false;
}

VisDomActionRef::~VisDomActionRef()
{
}

void VisDomActionRef::read(QXmlStreamReader &reader)
{

	const QXmlStreamAttributes attributes = reader.attributes();
	//for (const QXmlStreamAttribute &attribute : attributes) {
	for (int i = 0; i < attributes.size(); i++) {
		const QXmlStreamAttribute &attribute = attributes.at(i);
		QStringRef name = attribute.name();
		if (name == QLatin1String("name")) {
			setAttributeName(attribute.value().toString());
			continue;
		}
		reader.raiseError(QLatin1String("Unexpected attribute ")/* + name*/);
	}

	for (bool finished = false; !finished && !reader.hasError();) {
		switch (reader.readNext()) {
		case QXmlStreamReader::StartElement : {
			const QString tag = reader.name().toString().toLower();
			reader.raiseError(QLatin1String("Unexpected element ") + tag);
											  }
											  break;
		case QXmlStreamReader::EndElement :
			finished = true;
			break;
		case QXmlStreamReader::Characters :
			if (!reader.isWhitespace())
				m_text.append(reader.text().toString());
			break;
		default :
			break;
		}
	}
}

void VisDomActionRef::write(QXmlStreamWriter &writer, const QString &tagName) const
{
	writer.writeStartElement(tagName.isEmpty() ? QString::fromUtf8("actionref") : tagName.toLower());

	if (hasAttributeName())
		writer.writeAttribute(QStringLiteral("name"), attributeName());

	if (!m_text.isEmpty())
		writer.writeCharacters(m_text);

	writer.writeEndElement();
}

void VisDomButtonGroup::clear(bool clear_all)
{
	qDeleteAll(m_property);
	m_property.clear();
	qDeleteAll(m_attribute);
	m_attribute.clear();

	if (clear_all) {
		m_text.clear();
		m_has_attr_name = false;
	}

	m_children = 0;
}

VisDomButtonGroup::VisDomButtonGroup()
{
	m_children = 0;
	m_has_attr_name = false;
}

VisDomButtonGroup::~VisDomButtonGroup()
{
	qDeleteAll(m_property);
	m_property.clear();
	qDeleteAll(m_attribute);
	m_attribute.clear();
}

void VisDomButtonGroup::read(QXmlStreamReader &reader)
{

	const QXmlStreamAttributes attributes = reader.attributes();
	//for (const QXmlStreamAttribute &attribute : attributes) {
	for (int i = 0; i < attributes.size(); i++) {
		const QXmlStreamAttribute &attribute = attributes.at(i);
		QStringRef name = attribute.name();
		if (name == QLatin1String("name")) {
			setAttributeName(attribute.value().toString());
			continue;
		}
		reader.raiseError(QLatin1String("Unexpected attribute ")/* + name*/);
	}

	for (bool finished = false; !finished && !reader.hasError();) {
		switch (reader.readNext()) {
		case QXmlStreamReader::StartElement : {
			const QString tag = reader.name().toString().toLower();
			if (tag == QLatin1String("property")) {
				VisDomProperty *v = new VisDomProperty();
				v->read(reader);
				m_property.append(v);
				continue;
			}
			if (tag == QLatin1String("attribute")) {
				VisDomProperty *v = new VisDomProperty();
				v->read(reader);
				m_attribute.append(v);
				continue;
			}
			reader.raiseError(QLatin1String("Unexpected element ") + tag);
											  }
											  break;
		case QXmlStreamReader::EndElement :
			finished = true;
			break;
		case QXmlStreamReader::Characters :
			if (!reader.isWhitespace())
				m_text.append(reader.text().toString());
			break;
		default :
			break;
		}
	}
}

void VisDomButtonGroup::write(QXmlStreamWriter &writer, const QString &tagName) const
{
	writer.writeStartElement(tagName.isEmpty() ? QString::fromUtf8("buttongroup") : tagName.toLower());

	if (hasAttributeName())
		writer.writeAttribute(QStringLiteral("name"), attributeName());

	for (int i = 0; i < m_property.size(); ++i) {
		VisDomProperty* v = m_property[i];
		v->write(writer, QStringLiteral("property"));
	}
	for (int i = 0; i < m_attribute.size(); ++i) {
		VisDomProperty* v = m_attribute[i];
		v->write(writer, QStringLiteral("attribute"));
	}
	if (!m_text.isEmpty())
		writer.writeCharacters(m_text);

	writer.writeEndElement();
}

void VisDomButtonGroup::setElementProperty(const QList<VisDomProperty*>& a)
{
	m_children |= Property;
	m_property = a;
}

void VisDomButtonGroup::setElementAttribute(const QList<VisDomProperty*>& a)
{
	m_children |= Attribute;
	m_attribute = a;
}

void VisDomButtonGroups::clear(bool clear_all)
{
	qDeleteAll(m_buttonGroup);
	m_buttonGroup.clear();

	if (clear_all) {
		m_text.clear();
	}

	m_children = 0;
}

VisDomButtonGroups::VisDomButtonGroups()
{
	m_children = 0;
}

VisDomButtonGroups::~VisDomButtonGroups()
{
	qDeleteAll(m_buttonGroup);
	m_buttonGroup.clear();
}

void VisDomButtonGroups::read(QXmlStreamReader &reader)
{

	for (bool finished = false; !finished && !reader.hasError();) {
		switch (reader.readNext()) {
		case QXmlStreamReader::StartElement : {
			const QString tag = reader.name().toString().toLower();
			if (tag == QLatin1String("buttongroup")) {
				VisDomButtonGroup *v = new VisDomButtonGroup();
				v->read(reader);
				m_buttonGroup.append(v);
				continue;
			}
			reader.raiseError(QLatin1String("Unexpected element ") + tag);
											  }
											  break;
		case QXmlStreamReader::EndElement :
			finished = true;
			break;
		case QXmlStreamReader::Characters :
			if (!reader.isWhitespace())
				m_text.append(reader.text().toString());
			break;
		default :
			break;
		}
	}
}

void VisDomButtonGroups::write(QXmlStreamWriter &writer, const QString &tagName) const
{
	writer.writeStartElement(tagName.isEmpty() ? QString::fromUtf8("buttongroups") : tagName.toLower());

	for (int i = 0; i < m_buttonGroup.size(); ++i) {
		VisDomButtonGroup* v = m_buttonGroup[i];
		v->write(writer, QStringLiteral("buttongroup"));
	}
	if (!m_text.isEmpty())
		writer.writeCharacters(m_text);

	writer.writeEndElement();
}

void VisDomButtonGroups::setElementButtonGroup(const QList<VisDomButtonGroup*>& a)
{
	m_children |= ButtonGroup;
	m_buttonGroup = a;
}

void VisDomImages::clear(bool clear_all)
{
	qDeleteAll(m_image);
	m_image.clear();

	if (clear_all) {
		m_text.clear();
	}

	m_children = 0;
}

VisDomImages::VisDomImages()
{
	m_children = 0;
}

VisDomImages::~VisDomImages()
{
	qDeleteAll(m_image);
	m_image.clear();
}

void VisDomImages::read(QXmlStreamReader &reader)
{

	for (bool finished = false; !finished && !reader.hasError();) {
		switch (reader.readNext()) {
		case QXmlStreamReader::StartElement : {
			const QString tag = reader.name().toString().toLower();
			if (tag == QLatin1String("image")) {
				VisDomImage *v = new VisDomImage();
				v->read(reader);
				m_image.append(v);
				continue;
			}
			reader.raiseError(QLatin1String("Unexpected element ") + tag);
											  }
											  break;
		case QXmlStreamReader::EndElement :
			finished = true;
			break;
		case QXmlStreamReader::Characters :
			if (!reader.isWhitespace())
				m_text.append(reader.text().toString());
			break;
		default :
			break;
		}
	}
}

void VisDomImages::write(QXmlStreamWriter &writer, const QString &tagName) const
{
	writer.writeStartElement(tagName.isEmpty() ? QString::fromUtf8("images") : tagName.toLower());

	for (int i = 0; i < m_image.size(); ++i) {
		VisDomImage* v = m_image[i];
		v->write(writer, QStringLiteral("image"));
	}
	if (!m_text.isEmpty())
		writer.writeCharacters(m_text);

	writer.writeEndElement();
}

void VisDomImages::setElementImage(const QList<VisDomImage*>& a)
{
	m_children |= Image;
	m_image = a;
}

void VisDomImage::clear(bool clear_all)
{
	delete m_data;

	if (clear_all) {
		m_text.clear();
		m_has_attr_name = false;
	}

	m_children = 0;
	m_data = 0;
}

VisDomImage::VisDomImage()
{
	m_children = 0;
	m_has_attr_name = false;
	m_data = 0;
}

VisDomImage::~VisDomImage()
{
	delete m_data;
}

void VisDomImage::read(QXmlStreamReader &reader)
{

	const QXmlStreamAttributes attributes = reader.attributes();
	//for (const QXmlStreamAttribute &attribute : attributes) {
	for (int i = 0; i < attributes.size(); i++) {
		const QXmlStreamAttribute &attribute = attributes.at(i);
		QStringRef name = attribute.name();
		if (name == QLatin1String("name")) {
			setAttributeName(attribute.value().toString());
			continue;
		}
		reader.raiseError(QLatin1String("Unexpected attribute ")/* + name*/);
	}

	for (bool finished = false; !finished && !reader.hasError();) {
		switch (reader.readNext()) {
		case QXmlStreamReader::StartElement : {
			const QString tag = reader.name().toString().toLower();
			if (tag == QLatin1String("data")) {
				VisDomImageData *v = new VisDomImageData();
				v->read(reader);
				setElementData(v);
				continue;
			}
			reader.raiseError(QLatin1String("Unexpected element ") + tag);
											  }
											  break;
		case QXmlStreamReader::EndElement :
			finished = true;
			break;
		case QXmlStreamReader::Characters :
			if (!reader.isWhitespace())
				m_text.append(reader.text().toString());
			break;
		default :
			break;
		}
	}
}

void VisDomImage::write(QXmlStreamWriter &writer, const QString &tagName) const
{
	writer.writeStartElement(tagName.isEmpty() ? QString::fromUtf8("image") : tagName.toLower());

	if (hasAttributeName())
		writer.writeAttribute(QStringLiteral("name"), attributeName());

	if (m_children & Data) {
		m_data->write(writer, QStringLiteral("data"));
	}

	if (!m_text.isEmpty())
		writer.writeCharacters(m_text);

	writer.writeEndElement();
}

VisDomImageData* VisDomImage::takeElementData()
{
	VisDomImageData* a = m_data;
	m_data = 0;
	m_children ^= Data;
	return a;
}

void VisDomImage::setElementData(VisDomImageData* a)
{
	delete m_data;
	m_children |= Data;
	m_data = a;
}

void VisDomImage::clearElementData()
{
	delete m_data;
	m_data = 0;
	m_children &= ~Data;
}

void VisDomImageData::clear(bool clear_all)
{

	if (clear_all) {
		m_text.clear();
		m_has_attr_format = false;
		m_has_attr_length = false;
		m_attr_length = 0;
	}

	m_children = 0;
}

VisDomImageData::VisDomImageData()
{
	m_children = 0;
	m_has_attr_format = false;
	m_has_attr_length = false;
	m_attr_length = 0;
	m_text.clear();
}

VisDomImageData::~VisDomImageData()
{
}

void VisDomImageData::read(QXmlStreamReader &reader)
{

	const QXmlStreamAttributes attributes = reader.attributes();
	//for (const QXmlStreamAttribute &attribute : attributes) {
	for (int i = 0; i < attributes.size(); i++) {
		const QXmlStreamAttribute &attribute = attributes.at(i);
		QStringRef name = attribute.name();
		if (name == QLatin1String("format")) {
			setAttributeFormat(attribute.value().toString());
			continue;
		}
		if (name == QLatin1String("length")) {
			setAttributeLength(attribute.value().toInt());
			continue;
		}
		reader.raiseError(QLatin1String("Unexpected attribute ")/* + name*/);
	}

	for (bool finished = false; !finished && !reader.hasError();) {
		switch (reader.readNext()) {
		case QXmlStreamReader::StartElement : {
			const QString tag = reader.name().toString().toLower();
			reader.raiseError(QLatin1String("Unexpected element ") + tag);
											  }
											  break;
		case QXmlStreamReader::EndElement :
			finished = true;
			break;
		case QXmlStreamReader::Characters :
			if (!reader.isWhitespace())
				m_text.append(reader.text().toString());
			break;
		default :
			break;
		}
	}
}

void VisDomImageData::write(QXmlStreamWriter &writer, const QString &tagName) const
{
	writer.writeStartElement(tagName.isEmpty() ? QString::fromUtf8("imagedata") : tagName.toLower());

	if (hasAttributeFormat())
		writer.writeAttribute(QStringLiteral("format"), attributeFormat());

	if (hasAttributeLength())
		writer.writeAttribute(QStringLiteral("length"), QString::number(attributeLength()));

	if (!m_text.isEmpty())
		writer.writeCharacters(m_text);

	writer.writeEndElement();
}

void VisDomCustomWidgets::clear(bool clear_all)
{
	qDeleteAll(m_customWidget);
	m_customWidget.clear();

	if (clear_all) {
		m_text.clear();
	}

	m_children = 0;
}

VisDomCustomWidgets::VisDomCustomWidgets()
{
	m_children = 0;
}

VisDomCustomWidgets::~VisDomCustomWidgets()
{
	qDeleteAll(m_customWidget);
	m_customWidget.clear();
}

void VisDomCustomWidgets::read(QXmlStreamReader &reader)
{

	for (bool finished = false; !finished && !reader.hasError();) {
		switch (reader.readNext()) {
		case QXmlStreamReader::StartElement : {
			const QString tag = reader.name().toString().toLower();
			if (tag == QLatin1String("customwidget")) {
				VisDomCustomWidget *v = new VisDomCustomWidget();
				v->read(reader);
				m_customWidget.append(v);
				continue;
			}
			reader.raiseError(QLatin1String("Unexpected element ") + tag);
											  }
											  break;
		case QXmlStreamReader::EndElement :
			finished = true;
			break;
		case QXmlStreamReader::Characters :
			if (!reader.isWhitespace())
				m_text.append(reader.text().toString());
			break;
		default :
			break;
		}
	}
}

void VisDomCustomWidgets::write(QXmlStreamWriter &writer, const QString &tagName) const
{
	writer.writeStartElement(tagName.isEmpty() ? QString::fromUtf8("customwidgets") : tagName.toLower());

	for (int i = 0; i < m_customWidget.size(); ++i) {
		VisDomCustomWidget* v = m_customWidget[i];
		v->write(writer, QStringLiteral("customwidget"));
	}
	if (!m_text.isEmpty())
		writer.writeCharacters(m_text);

	writer.writeEndElement();
}

void VisDomCustomWidgets::setElementCustomWidget(const QList<VisDomCustomWidget*>& a)
{
	m_children |= CustomWidget;
	m_customWidget = a;
}

void VisDomHeader::clear(bool clear_all)
{

	if (clear_all) {
		m_text.clear();
		m_has_attr_location = false;
	}

	m_children = 0;
}

VisDomHeader::VisDomHeader()
{
	m_children = 0;
	m_has_attr_location = false;
	m_text.clear();
}

VisDomHeader::~VisDomHeader()
{
}

void VisDomHeader::read(QXmlStreamReader &reader)
{

	const QXmlStreamAttributes attributes = reader.attributes();
//	for (const QXmlStreamAttribute &attribute : attributes) {
	for (int i = 0; i < attributes.size(); i++) {
		const QXmlStreamAttribute &attribute = attributes.at(i);
		QStringRef name = attribute.name();
		if (name == QLatin1String("location")) {
			setAttributeLocation(attribute.value().toString());
			continue;
		}
		reader.raiseError(QLatin1String("Unexpected attribute ")/* + name*/);
	}

	for (bool finished = false; !finished && !reader.hasError();) {
		switch (reader.readNext()) {
		case QXmlStreamReader::StartElement : {
			const QString tag = reader.name().toString().toLower();
			reader.raiseError(QLatin1String("Unexpected element ") + tag);
											  }
											  break;
		case QXmlStreamReader::EndElement :
			finished = true;
			break;
		case QXmlStreamReader::Characters :
			if (!reader.isWhitespace())
				m_text.append(reader.text().toString());
			break;
		default :
			break;
		}
	}
}

void VisDomHeader::write(QXmlStreamWriter &writer, const QString &tagName) const
{
	writer.writeStartElement(tagName.isEmpty() ? QString::fromUtf8("header") : tagName.toLower());

	if (hasAttributeLocation())
		writer.writeAttribute(QStringLiteral("location"), attributeLocation());

	if (!m_text.isEmpty())
		writer.writeCharacters(m_text);

	writer.writeEndElement();
}

void VisDomCustomWidget::clear(bool clear_all)
{
	delete m_header;
	delete m_sizeHint;
	delete m_sizePolicy;
	delete m_script;
	delete m_properties;
	delete m_slots;
	delete m_propertyspecifications;

	if (clear_all) {
		m_text.clear();
	}

	m_children = 0;
	m_header = 0;
	m_sizeHint = 0;
	m_container = 0;
	m_sizePolicy = 0;
	m_script = 0;
	m_properties = 0;
	m_slots = 0;
	m_propertyspecifications = 0;
}

VisDomCustomWidget::VisDomCustomWidget()
{
	m_children = 0;
	m_header = 0;
	m_sizeHint = 0;
	m_container = 0;
	m_sizePolicy = 0;
	m_script = 0;
	m_properties = 0;
	m_slots = 0;
	m_propertyspecifications = 0;
}

VisDomCustomWidget::~VisDomCustomWidget()
{
	delete m_header;
	delete m_sizeHint;
	delete m_sizePolicy;
	delete m_script;
	delete m_properties;
	delete m_slots;
	delete m_propertyspecifications;
}

void VisDomCustomWidget::read(QXmlStreamReader &reader)
{

	for (bool finished = false; !finished && !reader.hasError();) {
		switch (reader.readNext()) {
		case QXmlStreamReader::StartElement : {
			const QString tag = reader.name().toString().toLower();
			if (tag == QLatin1String("class")) {
				setElementClass(reader.readElementText());
				continue;
			}
			if (tag == QLatin1String("extends")) {
				setElementExtends(reader.readElementText());
				continue;
			}
			if (tag == QLatin1String("header")) {
				VisDomHeader *v = new VisDomHeader();
				v->read(reader);
				setElementHeader(v);
				continue;
			}
			if (tag == QLatin1String("sizehint")) {
				VisDomSize *v = new VisDomSize();
				v->read(reader);
				setElementSizeHint(v);
				continue;
			}
			if (tag == QLatin1String("addpagemethod")) {
				setElementAddPageMethod(reader.readElementText());
				continue;
			}
			if (tag == QLatin1String("container")) {
				setElementContainer(reader.readElementText().toInt());
				continue;
			}
			if (tag == QLatin1String("sizepolicy")) {
				VisDomSizePolicyData *v = new VisDomSizePolicyData();
				v->read(reader);
				setElementSizePolicy(v);
				continue;
			}
			if (tag == QLatin1String("pixmap")) {
				setElementPixmap(reader.readElementText());
				continue;
			}
			if (tag == QLatin1String("script")) {
				VisDomScript *v = new VisDomScript();
				v->read(reader);
				setElementScript(v);
				continue;
			}
			if (tag == QLatin1String("properties")) {
				VisDomProperties *v = new VisDomProperties();
				v->read(reader);
				setElementProperties(v);
				continue;
			}
			if (tag == QLatin1String("slots")) {
				VisDomSlots *v = new VisDomSlots();
				v->read(reader);
				setElementSlots(v);
				continue;
			}
			if (tag == QLatin1String("propertyspecifications")) {
				VisDomPropertySpecifications *v = new VisDomPropertySpecifications();
				v->read(reader);
				setElementPropertyspecifications(v);
				continue;
			}
			reader.raiseError(QLatin1String("Unexpected element ") + tag);
											  }
											  break;
		case QXmlStreamReader::EndElement :
			finished = true;
			break;
		case QXmlStreamReader::Characters :
			if (!reader.isWhitespace())
				m_text.append(reader.text().toString());
			break;
		default :
			break;
		}
	}
}

void VisDomCustomWidget::write(QXmlStreamWriter &writer, const QString &tagName) const
{
	writer.writeStartElement(tagName.isEmpty() ? QString::fromUtf8("customwidget") : tagName.toLower());

	if (m_children & Class) {
		writer.writeTextElement(QStringLiteral("class"), m_class);
	}

	if (m_children & Extends) {
		writer.writeTextElement(QStringLiteral("extends"), m_extends);
	}

	if (m_children & Header) {
		m_header->write(writer, QStringLiteral("header"));
	}

	if (m_children & SizeHint) {
		m_sizeHint->write(writer, QStringLiteral("sizehint"));
	}

	if (m_children & AddPageMethod) {
		writer.writeTextElement(QStringLiteral("addpagemethod"), m_addPageMethod);
	}

	if (m_children & Container) {
		writer.writeTextElement(QStringLiteral("container"), QString::number(m_container));
	}

	if (m_children & SizePolicy) {
		m_sizePolicy->write(writer, QStringLiteral("sizepolicy"));
	}

	if (m_children & Pixmap) {
		writer.writeTextElement(QStringLiteral("pixmap"), m_pixmap);
	}

	if (m_children & Script) {
		m_script->write(writer, QStringLiteral("script"));
	}

	if (m_children & Properties) {
		m_properties->write(writer, QStringLiteral("properties"));
	}

	if (m_children & Slots) {
		m_slots->write(writer, QStringLiteral("slots"));
	}

	if (m_children & Propertyspecifications) {
		m_propertyspecifications->write(writer, QStringLiteral("propertyspecifications"));
	}

	if (!m_text.isEmpty())
		writer.writeCharacters(m_text);

	writer.writeEndElement();
}

void VisDomCustomWidget::setElementClass(const QString& a)
{
	m_children |= Class;
	m_class = a;
}

void VisDomCustomWidget::setElementExtends(const QString& a)
{
	m_children |= Extends;
	m_extends = a;
}

VisDomHeader* VisDomCustomWidget::takeElementHeader()
{
	VisDomHeader* a = m_header;
	m_header = 0;
	m_children ^= Header;
	return a;
}

void VisDomCustomWidget::setElementHeader(VisDomHeader* a)
{
	delete m_header;
	m_children |= Header;
	m_header = a;
}

VisDomSize* VisDomCustomWidget::takeElementSizeHint()
{
	VisDomSize* a = m_sizeHint;
	m_sizeHint = 0;
	m_children ^= SizeHint;
	return a;
}

void VisDomCustomWidget::setElementSizeHint(VisDomSize* a)
{
	delete m_sizeHint;
	m_children |= SizeHint;
	m_sizeHint = a;
}

void VisDomCustomWidget::setElementAddPageMethod(const QString& a)
{
	m_children |= AddPageMethod;
	m_addPageMethod = a;
}

void VisDomCustomWidget::setElementContainer(int a)
{
	m_children |= Container;
	m_container = a;
}

VisDomSizePolicyData* VisDomCustomWidget::takeElementSizePolicy()
{
	VisDomSizePolicyData* a = m_sizePolicy;
	m_sizePolicy = 0;
	m_children ^= SizePolicy;
	return a;
}

void VisDomCustomWidget::setElementSizePolicy(VisDomSizePolicyData* a)
{
	delete m_sizePolicy;
	m_children |= SizePolicy;
	m_sizePolicy = a;
}

void VisDomCustomWidget::setElementPixmap(const QString& a)
{
	m_children |= Pixmap;
	m_pixmap = a;
}

VisDomScript* VisDomCustomWidget::takeElementScript()
{
	VisDomScript* a = m_script;
	m_script = 0;
	m_children ^= Script;
	return a;
}

void VisDomCustomWidget::setElementScript(VisDomScript* a)
{
	delete m_script;
	m_children |= Script;
	m_script = a;
}

VisDomProperties* VisDomCustomWidget::takeElementProperties()
{
	VisDomProperties* a = m_properties;
	m_properties = 0;
	m_children ^= Properties;
	return a;
}

void VisDomCustomWidget::setElementProperties(VisDomProperties* a)
{
	delete m_properties;
	m_children |= Properties;
	m_properties = a;
}

VisDomSlots* VisDomCustomWidget::takeElementSlots()
{
	VisDomSlots* a = m_slots;
	m_slots = 0;
	m_children ^= Slots;
	return a;
}

void VisDomCustomWidget::setElementSlots(VisDomSlots* a)
{
	delete m_slots;
	m_children |= Slots;
	m_slots = a;
}

VisDomPropertySpecifications* VisDomCustomWidget::takeElementPropertyspecifications()
{
	VisDomPropertySpecifications* a = m_propertyspecifications;
	m_propertyspecifications = 0;
	m_children ^= Propertyspecifications;
	return a;
}

void VisDomCustomWidget::setElementPropertyspecifications(VisDomPropertySpecifications* a)
{
	delete m_propertyspecifications;
	m_children |= Propertyspecifications;
	m_propertyspecifications = a;
}

void VisDomCustomWidget::clearElementClass()
{
	m_children &= ~Class;
}

void VisDomCustomWidget::clearElementExtends()
{
	m_children &= ~Extends;
}

void VisDomCustomWidget::clearElementHeader()
{
	delete m_header;
	m_header = 0;
	m_children &= ~Header;
}

void VisDomCustomWidget::clearElementSizeHint()
{
	delete m_sizeHint;
	m_sizeHint = 0;
	m_children &= ~SizeHint;
}

void VisDomCustomWidget::clearElementAddPageMethod()
{
	m_children &= ~AddPageMethod;
}

void VisDomCustomWidget::clearElementContainer()
{
	m_children &= ~Container;
}

void VisDomCustomWidget::clearElementSizePolicy()
{
	delete m_sizePolicy;
	m_sizePolicy = 0;
	m_children &= ~SizePolicy;
}

void VisDomCustomWidget::clearElementPixmap()
{
	m_children &= ~Pixmap;
}

void VisDomCustomWidget::clearElementScript()
{
	delete m_script;
	m_script = 0;
	m_children &= ~Script;
}

void VisDomCustomWidget::clearElementProperties()
{
	delete m_properties;
	m_properties = 0;
	m_children &= ~Properties;
}

void VisDomCustomWidget::clearElementSlots()
{
	delete m_slots;
	m_slots = 0;
	m_children &= ~Slots;
}

void VisDomCustomWidget::clearElementPropertyspecifications()
{
	delete m_propertyspecifications;
	m_propertyspecifications = 0;
	m_children &= ~Propertyspecifications;
}

void VisDomProperties::clear(bool clear_all)
{
	qDeleteAll(m_property);
	m_property.clear();

	if (clear_all) {
		m_text.clear();
	}

	m_children = 0;
}

VisDomProperties::VisDomProperties()
{
	m_children = 0;
}

VisDomProperties::~VisDomProperties()
{
	qDeleteAll(m_property);
	m_property.clear();
}

void VisDomProperties::read(QXmlStreamReader &reader)
{

	for (bool finished = false; !finished && !reader.hasError();) {
		switch (reader.readNext()) {
		case QXmlStreamReader::StartElement : {
			const QString tag = reader.name().toString().toLower();
			if (tag == QLatin1String("property")) {
				VisDomPropertyData *v = new VisDomPropertyData();
				v->read(reader);
				m_property.append(v);
				continue;
			}
			reader.raiseError(QLatin1String("Unexpected element ") + tag);
											  }
											  break;
		case QXmlStreamReader::EndElement :
			finished = true;
			break;
		case QXmlStreamReader::Characters :
			if (!reader.isWhitespace())
				m_text.append(reader.text().toString());
			break;
		default :
			break;
		}
	}
}

void VisDomProperties::write(QXmlStreamWriter &writer, const QString &tagName) const
{
	writer.writeStartElement(tagName.isEmpty() ? QString::fromUtf8("properties") : tagName.toLower());

	for (int i = 0; i < m_property.size(); ++i) {
		VisDomPropertyData* v = m_property[i];
		v->write(writer, QStringLiteral("property"));
	}
	if (!m_text.isEmpty())
		writer.writeCharacters(m_text);

	writer.writeEndElement();
}

void VisDomProperties::setElementProperty(const QList<VisDomPropertyData*>& a)
{
	m_children |= Property;
	m_property = a;
}

void VisDomPropertyData::clear(bool clear_all)
{

	if (clear_all) {
		m_text.clear();
		m_has_attr_type = false;
	}

	m_children = 0;
}

VisDomPropertyData::VisDomPropertyData()
{
	m_children = 0;
	m_has_attr_type = false;
}

VisDomPropertyData::~VisDomPropertyData()
{
}

void VisDomPropertyData::read(QXmlStreamReader &reader)
{

	const QXmlStreamAttributes attributes = reader.attributes();
//	for (const QXmlStreamAttribute &attribute : attributes) {
	for (int i = 0; i < attributes.size(); i++) {
		const QXmlStreamAttribute &attribute = attributes.at(i);
		QStringRef name = attribute.name();
		if (name == QLatin1String("type")) {
			setAttributeType(attribute.value().toString());
			continue;
		}
		reader.raiseError(QLatin1String("Unexpected attribute ")/* + name*/);
	}

	for (bool finished = false; !finished && !reader.hasError();) {
		switch (reader.readNext()) {
		case QXmlStreamReader::StartElement : {
			const QString tag = reader.name().toString().toLower();
			reader.raiseError(QLatin1String("Unexpected element ") + tag);
											  }
											  break;
		case QXmlStreamReader::EndElement :
			finished = true;
			break;
		case QXmlStreamReader::Characters :
			if (!reader.isWhitespace())
				m_text.append(reader.text().toString());
			break;
		default :
			break;
		}
	}
}

void VisDomPropertyData::write(QXmlStreamWriter &writer, const QString &tagName) const
{
	writer.writeStartElement(tagName.isEmpty() ? QString::fromUtf8("propertydata") : tagName.toLower());

	if (hasAttributeType())
		writer.writeAttribute(QStringLiteral("type"), attributeType());

	if (!m_text.isEmpty())
		writer.writeCharacters(m_text);

	writer.writeEndElement();
}

void VisDomSizePolicyData::clear(bool clear_all)
{

	if (clear_all) {
		m_text.clear();
	}

	m_children = 0;
	m_horData = 0;
	m_verData = 0;
}

VisDomSizePolicyData::VisDomSizePolicyData()
{
	m_children = 0;
	m_horData = 0;
	m_verData = 0;
}

VisDomSizePolicyData::~VisDomSizePolicyData()
{
}

void VisDomSizePolicyData::read(QXmlStreamReader &reader)
{

	for (bool finished = false; !finished && !reader.hasError();) {
		switch (reader.readNext()) {
		case QXmlStreamReader::StartElement : {
			const QString tag = reader.name().toString().toLower();
			if (tag == QLatin1String("hordata")) {
				setElementHorData(reader.readElementText().toInt());
				continue;
			}
			if (tag == QLatin1String("verdata")) {
				setElementVerData(reader.readElementText().toInt());
				continue;
			}
			reader.raiseError(QLatin1String("Unexpected element ") + tag);
											  }
											  break;
		case QXmlStreamReader::EndElement :
			finished = true;
			break;
		case QXmlStreamReader::Characters :
			if (!reader.isWhitespace())
				m_text.append(reader.text().toString());
			break;
		default :
			break;
		}
	}
}

void VisDomSizePolicyData::write(QXmlStreamWriter &writer, const QString &tagName) const
{
	writer.writeStartElement(tagName.isEmpty() ? QString::fromUtf8("sizepolicydata") : tagName.toLower());

	if (m_children & HorData) {
		writer.writeTextElement(QStringLiteral("hordata"), QString::number(m_horData));
	}

	if (m_children & VerData) {
		writer.writeTextElement(QStringLiteral("verdata"), QString::number(m_verData));
	}

	if (!m_text.isEmpty())
		writer.writeCharacters(m_text);

	writer.writeEndElement();
}

void VisDomSizePolicyData::setElementHorData(int a)
{
	m_children |= HorData;
	m_horData = a;
}

void VisDomSizePolicyData::setElementVerData(int a)
{
	m_children |= VerData;
	m_verData = a;
}

void VisDomSizePolicyData::clearElementHorData()
{
	m_children &= ~HorData;
}

void VisDomSizePolicyData::clearElementVerData()
{
	m_children &= ~VerData;
}

void VisDomLayoutDefault::clear(bool clear_all)
{

	if (clear_all) {
		m_text.clear();
		m_has_attr_spacing = false;
		m_attr_spacing = 0;
		m_has_attr_margin = false;
		m_attr_margin = 0;
	}

	m_children = 0;
}

VisDomLayoutDefault::VisDomLayoutDefault()
{
	m_children = 0;
	m_has_attr_spacing = false;
	m_attr_spacing = 0;
	m_has_attr_margin = false;
	m_attr_margin = 0;
}

VisDomLayoutDefault::~VisDomLayoutDefault()
{
}

void VisDomLayoutDefault::read(QXmlStreamReader &reader)
{

	const QXmlStreamAttributes attributes = reader.attributes();
//	for (const QXmlStreamAttribute &attribute : attributes) {
	for (int i = 0; i < attributes.size(); i++) {
		const QXmlStreamAttribute &attribute = attributes.at(i);
		QStringRef name = attribute.name();
		if (name == QLatin1String("spacing")) {
			setAttributeSpacing(attribute.value().toInt());
			continue;
		}
		if (name == QLatin1String("margin")) {
			setAttributeMargin(attribute.value().toInt());
			continue;
		}
		reader.raiseError(QLatin1String("Unexpected attribute ")/* + name*/);
	}

	for (bool finished = false; !finished && !reader.hasError();) {
		switch (reader.readNext()) {
		case QXmlStreamReader::StartElement : {
			const QString tag = reader.name().toString().toLower();
			reader.raiseError(QLatin1String("Unexpected element ") + tag);
											  }
											  break;
		case QXmlStreamReader::EndElement :
			finished = true;
			break;
		case QXmlStreamReader::Characters :
			if (!reader.isWhitespace())
				m_text.append(reader.text().toString());
			break;
		default :
			break;
		}
	}
}

void VisDomLayoutDefault::write(QXmlStreamWriter &writer, const QString &tagName) const
{
	writer.writeStartElement(tagName.isEmpty() ? QString::fromUtf8("layoutdefault") : tagName.toLower());

	if (hasAttributeSpacing())
		writer.writeAttribute(QStringLiteral("spacing"), QString::number(attributeSpacing()));

	if (hasAttributeMargin())
		writer.writeAttribute(QStringLiteral("margin"), QString::number(attributeMargin()));

	if (!m_text.isEmpty())
		writer.writeCharacters(m_text);

	writer.writeEndElement();
}

void VisDomLayoutFunction::clear(bool clear_all)
{

	if (clear_all) {
		m_text.clear();
		m_has_attr_spacing = false;
		m_has_attr_margin = false;
	}

	m_children = 0;
}

VisDomLayoutFunction::VisDomLayoutFunction()
{
	m_children = 0;
	m_has_attr_spacing = false;
	m_has_attr_margin = false;
}

VisDomLayoutFunction::~VisDomLayoutFunction()
{
}

void VisDomLayoutFunction::read(QXmlStreamReader &reader)
{

	const QXmlStreamAttributes attributes = reader.attributes();
//	for (const QXmlStreamAttribute &attribute : attributes) {
	for (int i = 0; i < attributes.size(); i++) {
		const QXmlStreamAttribute &attribute = attributes.at(i);
		QStringRef name = attribute.name();
		if (name == QLatin1String("spacing")) {
			setAttributeSpacing(attribute.value().toString());
			continue;
		}
		if (name == QLatin1String("margin")) {
			setAttributeMargin(attribute.value().toString());
			continue;
		}
		reader.raiseError(QLatin1String("Unexpected attribute ")/* + name*/);
	}

	for (bool finished = false; !finished && !reader.hasError();) {
		switch (reader.readNext()) {
		case QXmlStreamReader::StartElement : {
			const QString tag = reader.name().toString().toLower();
			reader.raiseError(QLatin1String("Unexpected element ") + tag);
											  }
											  break;
		case QXmlStreamReader::EndElement :
			finished = true;
			break;
		case QXmlStreamReader::Characters :
			if (!reader.isWhitespace())
				m_text.append(reader.text().toString());
			break;
		default :
			break;
		}
	}
}

void VisDomLayoutFunction::write(QXmlStreamWriter &writer, const QString &tagName) const
{
	writer.writeStartElement(tagName.isEmpty() ? QString::fromUtf8("layoutfunction") : tagName.toLower());

	if (hasAttributeSpacing())
		writer.writeAttribute(QStringLiteral("spacing"), attributeSpacing());

	if (hasAttributeMargin())
		writer.writeAttribute(QStringLiteral("margin"), attributeMargin());

	if (!m_text.isEmpty())
		writer.writeCharacters(m_text);

	writer.writeEndElement();
}

void VisDomTabStops::clear(bool clear_all)
{
	m_tabStop.clear();

	if (clear_all) {
		m_text.clear();
	}

	m_children = 0;
}

VisDomTabStops::VisDomTabStops()
{
	m_children = 0;
}

VisDomTabStops::~VisDomTabStops()
{
	m_tabStop.clear();
}

void VisDomTabStops::read(QXmlStreamReader &reader)
{

	for (bool finished = false; !finished && !reader.hasError();) {
		switch (reader.readNext()) {
		case QXmlStreamReader::StartElement : {
			const QString tag = reader.name().toString().toLower();
			if (tag == QLatin1String("tabstop")) {
				m_tabStop.append(reader.readElementText());
				continue;
			}
			reader.raiseError(QLatin1String("Unexpected element ") + tag);
											  }
											  break;
		case QXmlStreamReader::EndElement :
			finished = true;
			break;
		case QXmlStreamReader::Characters :
			if (!reader.isWhitespace())
				m_text.append(reader.text().toString());
			break;
		default :
			break;
		}
	}
}

void VisDomTabStops::write(QXmlStreamWriter &writer, const QString &tagName) const
{
	writer.writeStartElement(tagName.isEmpty() ? QString::fromUtf8("tabstops") : tagName.toLower());

	for (int i = 0; i < m_tabStop.size(); ++i) {
		QString v = m_tabStop[i];
		writer.writeTextElement(QStringLiteral("tabstop"), v);
	}
	if (!m_text.isEmpty())
		writer.writeCharacters(m_text);

	writer.writeEndElement();
}

void VisDomTabStops::setElementTabStop(const QStringList& a)
{
	m_children |= TabStop;
	m_tabStop = a;
}

void VisDomLayout::clear(bool clear_all)
{
	qDeleteAll(m_property);
	m_property.clear();
	qDeleteAll(m_attribute);
	m_attribute.clear();
	qDeleteAll(m_item);
	m_item.clear();

	if (clear_all) {
		m_text.clear();
		m_has_attr_class = false;
		m_has_attr_name = false;
		m_has_attr_stretch = false;
		m_has_attr_rowStretch = false;
		m_has_attr_columnStretch = false;
		m_has_attr_rowMinimumHeight = false;
		m_has_attr_columnMinimumWidth = false;
	}

	m_children = 0;
}

VisDomLayout::VisDomLayout()
{
	m_children = 0;
	m_has_attr_class = false;
	m_has_attr_name = false;
	m_has_attr_stretch = false;
	m_has_attr_rowStretch = false;
	m_has_attr_columnStretch = false;
	m_has_attr_rowMinimumHeight = false;
	m_has_attr_columnMinimumWidth = false;
}

VisDomLayout::~VisDomLayout()
{
	qDeleteAll(m_property);
	m_property.clear();
	qDeleteAll(m_attribute);
	m_attribute.clear();
	qDeleteAll(m_item);
	m_item.clear();
}

void VisDomLayout::read(QXmlStreamReader &reader)
{

	const QXmlStreamAttributes attributes = reader.attributes();
//	for (const QXmlStreamAttribute &attribute : attributes) {
	for (int i = 0; i < attributes.size(); i++) {
		const QXmlStreamAttribute &attribute = attributes.at(i);
		QStringRef name = attribute.name();
		if (name == QLatin1String("class")) {
			setAttributeClass(attribute.value().toString());
			continue;
		}
		if (name == QLatin1String("name")) {
			setAttributeName(attribute.value().toString());
			continue;
		}
		if (name == QLatin1String("stretch")) {
			setAttributeStretch(attribute.value().toString());
			continue;
		}
		if (name == QLatin1String("rowstretch")) {
			setAttributeRowStretch(attribute.value().toString());
			continue;
		}
		if (name == QLatin1String("columnstretch")) {
			setAttributeColumnStretch(attribute.value().toString());
			continue;
		}
		if (name == QLatin1String("rowminimumheight")) {
			setAttributeRowMinimumHeight(attribute.value().toString());
			continue;
		}
		if (name == QLatin1String("columnminimumwidth")) {
			setAttributeColumnMinimumWidth(attribute.value().toString());
			continue;
		}
		reader.raiseError(QLatin1String("Unexpected attribute ")/* + name*/);
	}

	for (bool finished = false; !finished && !reader.hasError();) {
		switch (reader.readNext()) {
		case QXmlStreamReader::StartElement : {
			const QString tag = reader.name().toString().toLower();
			if (tag == QLatin1String("property")) {
				VisDomProperty *v = new VisDomProperty();
				v->read(reader);
				m_property.append(v);
				continue;
			}
			if (tag == QLatin1String("attribute")) {
				VisDomProperty *v = new VisDomProperty();
				v->read(reader);
				m_attribute.append(v);
				continue;
			}
			if (tag == QLatin1String("item")) {
				VisDomLayoutItem *v = new VisDomLayoutItem();
				v->read(reader);
				m_item.append(v);
				continue;
			}
			reader.raiseError(QLatin1String("Unexpected element ") + tag);
											  }
											  break;
		case QXmlStreamReader::EndElement :
			finished = true;
			break;
		case QXmlStreamReader::Characters :
			if (!reader.isWhitespace())
				m_text.append(reader.text().toString());
			break;
		default :
			break;
		}
	}
}

void VisDomLayout::write(QXmlStreamWriter &writer, const QString &tagName) const
{
	writer.writeStartElement(tagName.isEmpty() ? QString::fromUtf8("layout") : tagName.toLower());

	if (hasAttributeClass())
		writer.writeAttribute(QStringLiteral("class"), attributeClass());

	if (hasAttributeName())
		writer.writeAttribute(QStringLiteral("name"), attributeName());

	if (hasAttributeStretch())
		writer.writeAttribute(QStringLiteral("stretch"), attributeStretch());

	if (hasAttributeRowStretch())
		writer.writeAttribute(QStringLiteral("rowstretch"), attributeRowStretch());

	if (hasAttributeColumnStretch())
		writer.writeAttribute(QStringLiteral("columnstretch"), attributeColumnStretch());

	if (hasAttributeRowMinimumHeight())
		writer.writeAttribute(QStringLiteral("rowminimumheight"), attributeRowMinimumHeight());

	if (hasAttributeColumnMinimumWidth())
		writer.writeAttribute(QStringLiteral("columnminimumwidth"), attributeColumnMinimumWidth());

	for (int i = 0; i < m_property.size(); ++i) {
		VisDomProperty* v = m_property[i];
		v->write(writer, QStringLiteral("property"));
	}
	for (int i = 0; i < m_attribute.size(); ++i) {
		VisDomProperty* v = m_attribute[i];
		v->write(writer, QStringLiteral("attribute"));
	}
	for (int i = 0; i < m_item.size(); ++i) {
		VisDomLayoutItem* v = m_item[i];
		v->write(writer, QStringLiteral("item"));
	}
	if (!m_text.isEmpty())
		writer.writeCharacters(m_text);

	writer.writeEndElement();
}

void VisDomLayout::setElementProperty(const QList<VisDomProperty*>& a)
{
	m_children |= Property;
	m_property = a;
}

void VisDomLayout::setElementAttribute(const QList<VisDomProperty*>& a)
{
	m_children |= Attribute;
	m_attribute = a;
}

void VisDomLayout::setElementItem(const QList<VisDomLayoutItem*>& a)
{
	m_children |= Item;
	m_item = a;
}

void VisDomLayoutItem::clear(bool clear_all)
{
	delete m_widget;
	delete m_layout;
	delete m_spacer;

	if (clear_all) {
		m_text.clear();
		m_has_attr_row = false;
		m_attr_row = 0;
		m_has_attr_column = false;
		m_attr_column = 0;
		m_has_attr_rowSpan = false;
		m_attr_rowSpan = 0;
		m_has_attr_colSpan = false;
		m_attr_colSpan = 0;
		m_has_attr_alignment = false;
	}

	m_kind = Unknown;

	m_widget = 0;
	m_layout = 0;
	m_spacer = 0;
}

VisDomLayoutItem::VisDomLayoutItem()
{
	m_kind = Unknown;

	m_has_attr_row = false;
	m_attr_row = 0;
	m_has_attr_column = false;
	m_attr_column = 0;
	m_has_attr_rowSpan = false;
	m_attr_rowSpan = 0;
	m_has_attr_colSpan = false;
	m_attr_colSpan = 0;
	m_has_attr_alignment = false;
	m_widget = 0;
	m_layout = 0;
	m_spacer = 0;
}

VisDomLayoutItem::~VisDomLayoutItem()
{
	delete m_widget;
	delete m_layout;
	delete m_spacer;
}

void VisDomLayoutItem::read(QXmlStreamReader &reader)
{

	const QXmlStreamAttributes attributes = reader.attributes();
//	for (const QXmlStreamAttribute &attribute : attributes) {
	for (int i = 0; i < attributes.size(); i++) {
		const QXmlStreamAttribute &attribute = attributes.at(i);
		QStringRef name = attribute.name();
		if (name == QLatin1String("row")) {
			setAttributeRow(attribute.value().toInt());
			continue;
		}
		if (name == QLatin1String("column")) {
			setAttributeColumn(attribute.value().toInt());
			continue;
		}
		if (name == QLatin1String("rowspan")) {
			setAttributeRowSpan(attribute.value().toInt());
			continue;
		}
		if (name == QLatin1String("colspan")) {
			setAttributeColSpan(attribute.value().toInt());
			continue;
		}
		if (name == QLatin1String("alignment")) {
			setAttributeAlignment(attribute.value().toString());
			continue;
		}
		reader.raiseError(QLatin1String("Unexpected attribute ")/* + name*/);
	}

	for (bool finished = false; !finished && !reader.hasError();) {
		switch (reader.readNext()) {
		case QXmlStreamReader::StartElement : {
			const QString tag = reader.name().toString().toLower();
			if (tag == QLatin1String("widget")) {
				VisDomWidget *v = new VisDomWidget();
				v->read(reader);
				setElementWidget(v);
				continue;
			}
			if (tag == QLatin1String("layout")) {
				VisDomLayout *v = new VisDomLayout();
				v->read(reader);
				setElementLayout(v);
				continue;
			}
			if (tag == QLatin1String("spacer")) {
				VisDomSpacer *v = new VisDomSpacer();
				v->read(reader);
				setElementSpacer(v);
				continue;
			}
			reader.raiseError(QLatin1String("Unexpected element ") + tag);
											  }
											  break;
		case QXmlStreamReader::EndElement :
			finished = true;
			break;
		case QXmlStreamReader::Characters :
			if (!reader.isWhitespace())
				m_text.append(reader.text().toString());
			break;
		default :
			break;
		}
	}
}

void VisDomLayoutItem::write(QXmlStreamWriter &writer, const QString &tagName) const
{
	writer.writeStartElement(tagName.isEmpty() ? QString::fromUtf8("layoutitem") : tagName.toLower());

	if (hasAttributeRow())
		writer.writeAttribute(QStringLiteral("row"), QString::number(attributeRow()));

	if (hasAttributeColumn())
		writer.writeAttribute(QStringLiteral("column"), QString::number(attributeColumn()));

	if (hasAttributeRowSpan())
		writer.writeAttribute(QStringLiteral("rowspan"), QString::number(attributeRowSpan()));

	if (hasAttributeColSpan())
		writer.writeAttribute(QStringLiteral("colspan"), QString::number(attributeColSpan()));

	if (hasAttributeAlignment())
		writer.writeAttribute(QStringLiteral("alignment"), attributeAlignment());

	switch (kind()) {
	case Widget: {
		VisDomWidget* v = elementWidget();
		if (v != 0) {
			v->write(writer, QStringLiteral("widget"));
		}
		break;
				 }
	case Layout: {
		VisDomLayout* v = elementLayout();
		if (v != 0) {
			v->write(writer, QStringLiteral("layout"));
		}
		break;
				 }
	case Spacer: {
		VisDomSpacer* v = elementSpacer();
		if (v != 0) {
			v->write(writer, QStringLiteral("spacer"));
		}
		break;
				 }
	default:
		break;
	}
	if (!m_text.isEmpty())
		writer.writeCharacters(m_text);

	writer.writeEndElement();
}

VisDomWidget* VisDomLayoutItem::takeElementWidget()
{
	VisDomWidget* a = m_widget;
	m_widget = 0;
	return a;
}

void VisDomLayoutItem::setElementWidget(VisDomWidget* a)
{
	clear(false);
	m_kind = Widget;
	m_widget = a;
}

VisDomLayout* VisDomLayoutItem::takeElementLayout()
{
	VisDomLayout* a = m_layout;
	m_layout = 0;
	return a;
}

void VisDomLayoutItem::setElementLayout(VisDomLayout* a)
{
	clear(false);
	m_kind = Layout;
	m_layout = a;
}

VisDomSpacer* VisDomLayoutItem::takeElementSpacer()
{
	VisDomSpacer* a = m_spacer;
	m_spacer = 0;
	return a;
}

void VisDomLayoutItem::setElementSpacer(VisDomSpacer* a)
{
	clear(false);
	m_kind = Spacer;
	m_spacer = a;
}

void VisDomRow::clear(bool clear_all)
{
	qDeleteAll(m_property);
	m_property.clear();

	if (clear_all) {
		m_text.clear();
	}

	m_children = 0;
}

VisDomRow::VisDomRow()
{
	m_children = 0;
}

VisDomRow::~VisDomRow()
{
	qDeleteAll(m_property);
	m_property.clear();
}

void VisDomRow::read(QXmlStreamReader &reader)
{

	for (bool finished = false; !finished && !reader.hasError();) {
		switch (reader.readNext()) {
		case QXmlStreamReader::StartElement : {
			const QString tag = reader.name().toString().toLower();
			if (tag == QLatin1String("property")) {
				VisDomProperty *v = new VisDomProperty();
				v->read(reader);
				m_property.append(v);
				continue;
			}
			reader.raiseError(QLatin1String("Unexpected element ") + tag);
											  }
											  break;
		case QXmlStreamReader::EndElement :
			finished = true;
			break;
		case QXmlStreamReader::Characters :
			if (!reader.isWhitespace())
				m_text.append(reader.text().toString());
			break;
		default :
			break;
		}
	}
}

void VisDomRow::write(QXmlStreamWriter &writer, const QString &tagName) const
{
	writer.writeStartElement(tagName.isEmpty() ? QString::fromUtf8("row") : tagName.toLower());

	for (int i = 0; i < m_property.size(); ++i) {
		VisDomProperty* v = m_property[i];
		v->write(writer, QStringLiteral("property"));
	}
	if (!m_text.isEmpty())
		writer.writeCharacters(m_text);

	writer.writeEndElement();
}

void VisDomRow::setElementProperty(const QList<VisDomProperty*>& a)
{
	m_children |= Property;
	m_property = a;
}

void VisDomColumn::clear(bool clear_all)
{
	qDeleteAll(m_property);
	m_property.clear();

	if (clear_all) {
		m_text.clear();
	}

	m_children = 0;
}

VisDomColumn::VisDomColumn()
{
	m_children = 0;
}

VisDomColumn::~VisDomColumn()
{
	qDeleteAll(m_property);
	m_property.clear();
}

void VisDomColumn::read(QXmlStreamReader &reader)
{

	for (bool finished = false; !finished && !reader.hasError();) {
		switch (reader.readNext()) {
		case QXmlStreamReader::StartElement : {
			const QString tag = reader.name().toString().toLower();
			if (tag == QLatin1String("property")) {
				VisDomProperty *v = new VisDomProperty();
				v->read(reader);
				m_property.append(v);
				continue;
			}
			reader.raiseError(QLatin1String("Unexpected element ") + tag);
											  }
											  break;
		case QXmlStreamReader::EndElement :
			finished = true;
			break;
		case QXmlStreamReader::Characters :
			if (!reader.isWhitespace())
				m_text.append(reader.text().toString());
			break;
		default :
			break;
		}
	}
}

void VisDomColumn::write(QXmlStreamWriter &writer, const QString &tagName) const
{
	writer.writeStartElement(tagName.isEmpty() ? QString::fromUtf8("column") : tagName.toLower());

	for (int i = 0; i < m_property.size(); ++i) {
		VisDomProperty* v = m_property[i];
		v->write(writer, QStringLiteral("property"));
	}
	if (!m_text.isEmpty())
		writer.writeCharacters(m_text);

	writer.writeEndElement();
}

void VisDomColumn::setElementProperty(const QList<VisDomProperty*>& a)
{
	m_children |= Property;
	m_property = a;
}

void VisDomItem::clear(bool clear_all)
{
	qDeleteAll(m_property);
	m_property.clear();
	qDeleteAll(m_item);
	m_item.clear();

	if (clear_all) {
		m_text.clear();
		m_has_attr_row = false;
		m_attr_row = 0;
		m_has_attr_column = false;
		m_attr_column = 0;
	}

	m_children = 0;
}

VisDomItem::VisDomItem()
{
	m_children = 0;
	m_has_attr_row = false;
	m_attr_row = 0;
	m_has_attr_column = false;
	m_attr_column = 0;
}

VisDomItem::~VisDomItem()
{
	qDeleteAll(m_property);
	m_property.clear();
	qDeleteAll(m_item);
	m_item.clear();
}

void VisDomItem::read(QXmlStreamReader &reader)
{

	const QXmlStreamAttributes attributes = reader.attributes();
//	for (const QXmlStreamAttribute &attribute : attributes) {
	for (int i = 0; i < attributes.size(); i++) {
		const QXmlStreamAttribute &attribute = attributes.at(i);
		QStringRef name = attribute.name();
		if (name == QLatin1String("row")) {
			setAttributeRow(attribute.value().toInt());
			continue;
		}
		if (name == QLatin1String("column")) {
			setAttributeColumn(attribute.value().toInt());
			continue;
		}
		reader.raiseError(QLatin1String("Unexpected attribute ")/* + name*/);
	}

	for (bool finished = false; !finished && !reader.hasError();) {
		switch (reader.readNext()) {
		case QXmlStreamReader::StartElement : {
			const QString tag = reader.name().toString().toLower();
			if (tag == QLatin1String("property")) {
				VisDomProperty *v = new VisDomProperty();
				v->read(reader);
				m_property.append(v);
				continue;
			}
			if (tag == QLatin1String("item")) {
				VisDomItem *v = new VisDomItem();
				v->read(reader);
				m_item.append(v);
				continue;
			}
			reader.raiseError(QLatin1String("Unexpected element ") + tag);
											  }
											  break;
		case QXmlStreamReader::EndElement :
			finished = true;
			break;
		case QXmlStreamReader::Characters :
			if (!reader.isWhitespace())
				m_text.append(reader.text().toString());
			break;
		default :
			break;
		}
	}
}

void VisDomItem::write(QXmlStreamWriter &writer, const QString &tagName) const
{
	writer.writeStartElement(tagName.isEmpty() ? QString::fromUtf8("item") : tagName.toLower());

	if (hasAttributeRow())
		writer.writeAttribute(QStringLiteral("row"), QString::number(attributeRow()));

	if (hasAttributeColumn())
		writer.writeAttribute(QStringLiteral("column"), QString::number(attributeColumn()));

	for (int i = 0; i < m_property.size(); ++i) {
		VisDomProperty* v = m_property[i];
		v->write(writer, QStringLiteral("property"));
	}
	for (int i = 0; i < m_item.size(); ++i) {
		VisDomItem* v = m_item[i];
		v->write(writer, QStringLiteral("item"));
	}
	if (!m_text.isEmpty())
		writer.writeCharacters(m_text);

	writer.writeEndElement();
}

void VisDomItem::setElementProperty(const QList<VisDomProperty*>& a)
{
	m_children |= Property;
	m_property = a;
}

void VisDomItem::setElementItem(const QList<VisDomItem*>& a)
{
	m_children |= Item;
	m_item = a;
}

void VisDomWidget::clear(bool clear_all)
{
	m_class.clear();
	qDeleteAll(m_property);
	m_property.clear();
	qDeleteAll(m_script);
	m_script.clear();
	qDeleteAll(m_widgetData);
	m_widgetData.clear();
	qDeleteAll(m_attribute);
	m_attribute.clear();
	qDeleteAll(m_row);
	m_row.clear();
	qDeleteAll(m_column);
	m_column.clear();
	qDeleteAll(m_item);
	m_item.clear();
	qDeleteAll(m_layout);
	m_layout.clear();
	qDeleteAll(m_widget);
	m_widget.clear();
	qDeleteAll(m_action);
	m_action.clear();
	qDeleteAll(m_actionGroup);
	m_actionGroup.clear();
	qDeleteAll(m_addAction);
	m_addAction.clear();
	m_zOrder.clear();

	if (clear_all) {
		m_text.clear();
		m_has_attr_class = false;
		m_has_attr_name = false;
		m_has_attr_native = false;
		m_attr_native = false;
	}

	m_children = 0;
}

VisDomWidget::VisDomWidget()
{
	m_children = 0;
	m_has_attr_class = false;
	m_has_attr_name = false;
	m_has_attr_native = false;
	m_attr_native = false;
}

VisDomWidget::~VisDomWidget()
{
	m_class.clear();
	qDeleteAll(m_property);
	m_property.clear();
	qDeleteAll(m_script);
	m_script.clear();
	qDeleteAll(m_widgetData);
	m_widgetData.clear();
	qDeleteAll(m_attribute);
	m_attribute.clear();
	qDeleteAll(m_row);
	m_row.clear();
	qDeleteAll(m_column);
	m_column.clear();
	qDeleteAll(m_item);
	m_item.clear();
	qDeleteAll(m_layout);
	m_layout.clear();
	qDeleteAll(m_widget);
	m_widget.clear();
	qDeleteAll(m_action);
	m_action.clear();
	qDeleteAll(m_actionGroup);
	m_actionGroup.clear();
	qDeleteAll(m_addAction);
	m_addAction.clear();
	m_zOrder.clear();
}

void VisDomWidget::read(QXmlStreamReader &reader)
{

	const QXmlStreamAttributes attributes = reader.attributes();
//	for (const QXmlStreamAttribute &attribute : attributes) {
	for (int i = 0; i < attributes.size(); i++) {
		const QXmlStreamAttribute &attribute = attributes.at(i);
		QStringRef name = attribute.name();
		if (name == QLatin1String("class")) {
			setAttributeClass(attribute.value().toString());
			continue;
		}
		if (name == QLatin1String("name")) {
			setAttributeName(attribute.value().toString());
			continue;
		}
		if (name == QLatin1String("native")) {
			setAttributeNative(attribute.value() == QLatin1String("true"));
			continue;
		}
		reader.raiseError(QLatin1String("Unexpected attribute ")/* + name*/);
	}

	for (bool finished = false; !finished && !reader.hasError();) {
		switch (reader.readNext()) {
		case QXmlStreamReader::StartElement : {
			const QString tag = reader.name().toString().toLower();
			if (tag == QLatin1String("class")) {
				m_class.append(reader.readElementText());
				continue;
			}
			if (tag == QLatin1String("property")) {
				VisDomProperty *v = new VisDomProperty();
				v->read(reader);
				m_property.append(v);
				continue;
			}
			if (tag == QLatin1String("script")) {
				VisDomScript *v = new VisDomScript();
				v->read(reader);
				m_script.append(v);
				continue;
			}
			if (tag == QLatin1String("widgetdata")) {
				VisDomWidgetData *v = new VisDomWidgetData();
				v->read(reader);
				m_widgetData.append(v);
				continue;
			}
			if (tag == QLatin1String("attribute")) {
				VisDomProperty *v = new VisDomProperty();
				v->read(reader);
				m_attribute.append(v);
				continue;
			}
			if (tag == QLatin1String("row")) {
				VisDomRow *v = new VisDomRow();
				v->read(reader);
				m_row.append(v);
				continue;
			}
			if (tag == QLatin1String("column")) {
				VisDomColumn *v = new VisDomColumn();
				v->read(reader);
				m_column.append(v);
				continue;
			}
			if (tag == QLatin1String("item")) {
				VisDomItem *v = new VisDomItem();
				v->read(reader);
				m_item.append(v);
				continue;
			}
			if (tag == QLatin1String("layout")) {
				VisDomLayout *v = new VisDomLayout();
				v->read(reader);
				m_layout.append(v);
				continue;
			}
			if (tag == QLatin1String("widget")) {
				VisDomWidget *v = new VisDomWidget();
				v->read(reader);
				m_widget.append(v);
				continue;
			}
			if (tag == QLatin1String("action")) {
				VisDomAction *v = new VisDomAction();
				v->read(reader);
				m_action.append(v);
				continue;
			}
			if (tag == QLatin1String("actiongroup")) {
				VisDomActionGroup *v = new VisDomActionGroup();
				v->read(reader);
				m_actionGroup.append(v);
				continue;
			}
			if (tag == QLatin1String("addaction")) {
				VisDomActionRef *v = new VisDomActionRef();
				v->read(reader);
				m_addAction.append(v);
				continue;
			}
			if (tag == QLatin1String("zorder")) {
				m_zOrder.append(reader.readElementText());
				continue;
			}
			reader.raiseError(QLatin1String("Unexpected element ") + tag);
											  }
											  break;
		case QXmlStreamReader::EndElement :
			finished = true;
			break;
		case QXmlStreamReader::Characters :
			if (!reader.isWhitespace())
				m_text.append(reader.text().toString());
			break;
		default :
			break;
		}
	}
}

void VisDomWidget::write(QXmlStreamWriter &writer, const QString &tagName) const
{
	writer.writeStartElement(tagName.isEmpty() ? QString::fromUtf8("widget") : tagName.toLower());

	if (hasAttributeClass())
		writer.writeAttribute(QStringLiteral("class"), attributeClass());

	if (hasAttributeName())
		writer.writeAttribute(QStringLiteral("name"), attributeName());

	if (hasAttributeNative())
		writer.writeAttribute(QStringLiteral("native"), (attributeNative() ? QLatin1String("true") : QLatin1String("false")));

	for (int i = 0; i < m_class.size(); ++i) {
		QString v = m_class[i];
		writer.writeTextElement(QStringLiteral("class"), v);
	}
	for (int i = 0; i < m_property.size(); ++i) {
		VisDomProperty* v = m_property[i];
		v->write(writer, QStringLiteral("property"));
	}
	for (int i = 0; i < m_script.size(); ++i) {
		VisDomScript* v = m_script[i];
		v->write(writer, QStringLiteral("script"));
	}
	for (int i = 0; i < m_widgetData.size(); ++i) {
		VisDomWidgetData* v = m_widgetData[i];
		v->write(writer, QStringLiteral("widgetdata"));
	}
	for (int i = 0; i < m_attribute.size(); ++i) {
		VisDomProperty* v = m_attribute[i];
		v->write(writer, QStringLiteral("attribute"));
	}
	for (int i = 0; i < m_row.size(); ++i) {
		VisDomRow* v = m_row[i];
		v->write(writer, QStringLiteral("row"));
	}
	for (int i = 0; i < m_column.size(); ++i) {
		VisDomColumn* v = m_column[i];
		v->write(writer, QStringLiteral("column"));
	}
	for (int i = 0; i < m_item.size(); ++i) {
		VisDomItem* v = m_item[i];
		v->write(writer, QStringLiteral("item"));
	}
	for (int i = 0; i < m_layout.size(); ++i) {
		VisDomLayout* v = m_layout[i];
		v->write(writer, QStringLiteral("layout"));
	}
	for (int i = 0; i < m_widget.size(); ++i) {
		VisDomWidget* v = m_widget[i];
		v->write(writer, QStringLiteral("widget"));
	}
	for (int i = 0; i < m_action.size(); ++i) {
		VisDomAction* v = m_action[i];
		v->write(writer, QStringLiteral("action"));
	}
	for (int i = 0; i < m_actionGroup.size(); ++i) {
		VisDomActionGroup* v = m_actionGroup[i];
		v->write(writer, QStringLiteral("actiongroup"));
	}
	for (int i = 0; i < m_addAction.size(); ++i) {
		VisDomActionRef* v = m_addAction[i];
		v->write(writer, QStringLiteral("addaction"));
	}
	for (int i = 0; i < m_zOrder.size(); ++i) {
		QString v = m_zOrder[i];
		writer.writeTextElement(QStringLiteral("zorder"), v);
	}
	if (!m_text.isEmpty())
		writer.writeCharacters(m_text);

	writer.writeEndElement();
}

void VisDomWidget::setElementClass(const QStringList& a)
{
	m_children |= Class;
	m_class = a;
}

void VisDomWidget::setElementProperty(const QList<VisDomProperty*>& a)
{
	m_children |= Property;
	m_property = a;
}

void VisDomWidget::setElementScript(const QList<VisDomScript*>& a)
{
	m_children |= Script;
	m_script = a;
}

void VisDomWidget::setElementWidgetData(const QList<VisDomWidgetData*>& a)
{
	m_children |= WidgetData;
	m_widgetData = a;
}

void VisDomWidget::setElementAttribute(const QList<VisDomProperty*>& a)
{
	m_children |= Attribute;
	m_attribute = a;
}

void VisDomWidget::setElementRow(const QList<VisDomRow*>& a)
{
	m_children |= Row;
	m_row = a;
}

void VisDomWidget::setElementColumn(const QList<VisDomColumn*>& a)
{
	m_children |= Column;
	m_column = a;
}

void VisDomWidget::setElementItem(const QList<VisDomItem*>& a)
{
	m_children |= Item;
	m_item = a;
}

void VisDomWidget::setElementLayout(const QList<VisDomLayout*>& a)
{
	m_children |= Layout;
	m_layout = a;
}

void VisDomWidget::setElementWidget(const QList<VisDomWidget*>& a)
{
	m_children |= Widget;
	m_widget = a;
}

void VisDomWidget::setElementAction(const QList<VisDomAction*>& a)
{
	m_children |= Action;
	m_action = a;
}

void VisDomWidget::setElementActionGroup(const QList<VisDomActionGroup*>& a)
{
	m_children |= ActionGroup;
	m_actionGroup = a;
}

void VisDomWidget::setElementAddAction(const QList<VisDomActionRef*>& a)
{
	m_children |= AddAction;
	m_addAction = a;
}

void VisDomWidget::setElementZOrder(const QStringList& a)
{
	m_children |= ZOrder;
	m_zOrder = a;
}

void VisDomSpacer::clear(bool clear_all)
{
	qDeleteAll(m_property);
	m_property.clear();

	if (clear_all) {
		m_text.clear();
		m_has_attr_name = false;
	}

	m_children = 0;
}

VisDomSpacer::VisDomSpacer()
{
	m_children = 0;
	m_has_attr_name = false;
}

VisDomSpacer::~VisDomSpacer()
{
	qDeleteAll(m_property);
	m_property.clear();
}

void VisDomSpacer::read(QXmlStreamReader &reader)
{

	const QXmlStreamAttributes attributes = reader.attributes();
//	for (const QXmlStreamAttribute &attribute : attributes) {
	for (int i = 0; i < attributes.size(); i++) {
		const QXmlStreamAttribute &attribute = attributes.at(i);
		QStringRef name = attribute.name();
		if (name == QLatin1String("name")) {
			setAttributeName(attribute.value().toString());
			continue;
		}
		reader.raiseError(QLatin1String("Unexpected attribute ")/* + name*/);
	}

	for (bool finished = false; !finished && !reader.hasError();) {
		switch (reader.readNext()) {
		case QXmlStreamReader::StartElement : {
			const QString tag = reader.name().toString().toLower();
			if (tag == QLatin1String("property")) {
				VisDomProperty *v = new VisDomProperty();
				v->read(reader);
				m_property.append(v);
				continue;
			}
			reader.raiseError(QLatin1String("Unexpected element ") + tag);
											  }
											  break;
		case QXmlStreamReader::EndElement :
			finished = true;
			break;
		case QXmlStreamReader::Characters :
			if (!reader.isWhitespace())
				m_text.append(reader.text().toString());
			break;
		default :
			break;
		}
	}
}

void VisDomSpacer::write(QXmlStreamWriter &writer, const QString &tagName) const
{
	writer.writeStartElement(tagName.isEmpty() ? QString::fromUtf8("spacer") : tagName.toLower());

	if (hasAttributeName())
		writer.writeAttribute(QStringLiteral("name"), attributeName());

	for (int i = 0; i < m_property.size(); ++i) {
		VisDomProperty* v = m_property[i];
		v->write(writer, QStringLiteral("property"));
	}
	if (!m_text.isEmpty())
		writer.writeCharacters(m_text);

	writer.writeEndElement();
}

void VisDomSpacer::setElementProperty(const QList<VisDomProperty*>& a)
{
	m_children |= Property;
	m_property = a;
}

void VisDomColor::clear(bool clear_all)
{

	if (clear_all) {
		m_text.clear();
		m_has_attr_alpha = false;
		m_attr_alpha = 0;
	}

	m_children = 0;
	m_red = 0;
	m_green = 0;
	m_blue = 0;
}

VisDomColor::VisDomColor()
{
	m_children = 0;
	m_has_attr_alpha = false;
	m_attr_alpha = 0;
	m_red = 0;
	m_green = 0;
	m_blue = 0;
}

VisDomColor::~VisDomColor()
{
}

void VisDomColor::read(QXmlStreamReader &reader)
{

	const QXmlStreamAttributes attributes = reader.attributes();
//	for (const QXmlStreamAttribute &attribute : attributes) {
	for (int i = 0; i < attributes.size(); i++) {
		const QXmlStreamAttribute &attribute = attributes.at(i);
		QStringRef name = attribute.name();
		if (name == QLatin1String("alpha")) {
			setAttributeAlpha(attribute.value().toInt());
			continue;
		}
		reader.raiseError(QLatin1String("Unexpected attribute ")/* + name*/);
	}

	for (bool finished = false; !finished && !reader.hasError();) {
		switch (reader.readNext()) {
		case QXmlStreamReader::StartElement : {
			const QString tag = reader.name().toString().toLower();
			if (tag == QLatin1String("red")) {
				setElementRed(reader.readElementText().toInt());
				continue;
			}
			if (tag == QLatin1String("green")) {
				setElementGreen(reader.readElementText().toInt());
				continue;
			}
			if (tag == QLatin1String("blue")) {
				setElementBlue(reader.readElementText().toInt());
				continue;
			}
			reader.raiseError(QLatin1String("Unexpected element ") + tag);
											  }
											  break;
		case QXmlStreamReader::EndElement :
			finished = true;
			break;
		case QXmlStreamReader::Characters :
			if (!reader.isWhitespace())
				m_text.append(reader.text().toString());
			break;
		default :
			break;
		}
	}
}

void VisDomColor::write(QXmlStreamWriter &writer, const QString &tagName) const
{
	writer.writeStartElement(tagName.isEmpty() ? QString::fromUtf8("color") : tagName.toLower());

	if (hasAttributeAlpha())
		writer.writeAttribute(QStringLiteral("alpha"), QString::number(attributeAlpha()));

	if (m_children & Red) {
		writer.writeTextElement(QStringLiteral("red"), QString::number(m_red));
	}

	if (m_children & Green) {
		writer.writeTextElement(QStringLiteral("green"), QString::number(m_green));
	}

	if (m_children & Blue) {
		writer.writeTextElement(QStringLiteral("blue"), QString::number(m_blue));
	}

	if (!m_text.isEmpty())
		writer.writeCharacters(m_text);

	writer.writeEndElement();
}

void VisDomColor::setElementRed(int a)
{
	m_children |= Red;
	m_red = a;
}

void VisDomColor::setElementGreen(int a)
{
	m_children |= Green;
	m_green = a;
}

void VisDomColor::setElementBlue(int a)
{
	m_children |= Blue;
	m_blue = a;
}

void VisDomColor::clearElementRed()
{
	m_children &= ~Red;
}

void VisDomColor::clearElementGreen()
{
	m_children &= ~Green;
}

void VisDomColor::clearElementBlue()
{
	m_children &= ~Blue;
}

void VisDomGradientStop::clear(bool clear_all)
{
	delete m_color;

	if (clear_all) {
		m_text.clear();
		m_has_attr_position = false;
		m_attr_position = 0.0;
	}

	m_children = 0;
	m_color = 0;
}

VisDomGradientStop::VisDomGradientStop()
{
	m_children = 0;
	m_has_attr_position = false;
	m_attr_position = 0.0;
	m_color = 0;
}

VisDomGradientStop::~VisDomGradientStop()
{
	delete m_color;
}

void VisDomGradientStop::read(QXmlStreamReader &reader)
{

	const QXmlStreamAttributes attributes = reader.attributes();
//	for (const QXmlStreamAttribute &attribute : attributes) {
	for (int i = 0; i < attributes.size(); i++) {
		const QXmlStreamAttribute &attribute = attributes.at(i);
		QStringRef name = attribute.name();
		if (name == QLatin1String("position")) {
			setAttributePosition(attribute.value().toDouble());
			continue;
		}
		reader.raiseError(QLatin1String("Unexpected attribute ")/* + name*/);
	}

	for (bool finished = false; !finished && !reader.hasError();) {
		switch (reader.readNext()) {
		case QXmlStreamReader::StartElement : {
			const QString tag = reader.name().toString().toLower();
			if (tag == QLatin1String("color")) {
				VisDomColor *v = new VisDomColor();
				v->read(reader);
				setElementColor(v);
				continue;
			}
			reader.raiseError(QLatin1String("Unexpected element ") + tag);
											  }
											  break;
		case QXmlStreamReader::EndElement :
			finished = true;
			break;
		case QXmlStreamReader::Characters :
			if (!reader.isWhitespace())
				m_text.append(reader.text().toString());
			break;
		default :
			break;
		}
	}
}

void VisDomGradientStop::write(QXmlStreamWriter &writer, const QString &tagName) const
{
	writer.writeStartElement(tagName.isEmpty() ? QString::fromUtf8("gradientstop") : tagName.toLower());

	if (hasAttributePosition())
		writer.writeAttribute(QStringLiteral("position"), QString::number(attributePosition(), 'f', 15));

	if (m_children & Color) {
		m_color->write(writer, QStringLiteral("color"));
	}

	if (!m_text.isEmpty())
		writer.writeCharacters(m_text);

	writer.writeEndElement();
}

VisDomColor* VisDomGradientStop::takeElementColor()
{
	VisDomColor* a = m_color;
	m_color = 0;
	m_children ^= Color;
	return a;
}

void VisDomGradientStop::setElementColor(VisDomColor* a)
{
	delete m_color;
	m_children |= Color;
	m_color = a;
}

void VisDomGradientStop::clearElementColor()
{
	delete m_color;
	m_color = 0;
	m_children &= ~Color;
}

void VisDomGradient::clear(bool clear_all)
{
	qDeleteAll(m_gradientStop);
	m_gradientStop.clear();

	if (clear_all) {
		m_text.clear();
		m_has_attr_startX = false;
		m_attr_startX = 0.0;
		m_has_attr_startY = false;
		m_attr_startY = 0.0;
		m_has_attr_endX = false;
		m_attr_endX = 0.0;
		m_has_attr_endY = false;
		m_attr_endY = 0.0;
		m_has_attr_centralX = false;
		m_attr_centralX = 0.0;
		m_has_attr_centralY = false;
		m_attr_centralY = 0.0;
		m_has_attr_focalX = false;
		m_attr_focalX = 0.0;
		m_has_attr_focalY = false;
		m_attr_focalY = 0.0;
		m_has_attr_radius = false;
		m_attr_radius = 0.0;
		m_has_attr_angle = false;
		m_attr_angle = 0.0;
		m_has_attr_type = false;
		m_has_attr_spread = false;
		m_has_attr_coordinateMode = false;
	}

	m_children = 0;
}

VisDomGradient::VisDomGradient()
{
	m_children = 0;
	m_has_attr_startX = false;
	m_attr_startX = 0.0;
	m_has_attr_startY = false;
	m_attr_startY = 0.0;
	m_has_attr_endX = false;
	m_attr_endX = 0.0;
	m_has_attr_endY = false;
	m_attr_endY = 0.0;
	m_has_attr_centralX = false;
	m_attr_centralX = 0.0;
	m_has_attr_centralY = false;
	m_attr_centralY = 0.0;
	m_has_attr_focalX = false;
	m_attr_focalX = 0.0;
	m_has_attr_focalY = false;
	m_attr_focalY = 0.0;
	m_has_attr_radius = false;
	m_attr_radius = 0.0;
	m_has_attr_angle = false;
	m_attr_angle = 0.0;
	m_has_attr_type = false;
	m_has_attr_spread = false;
	m_has_attr_coordinateMode = false;
}

VisDomGradient::~VisDomGradient()
{
	qDeleteAll(m_gradientStop);
	m_gradientStop.clear();
}

void VisDomGradient::read(QXmlStreamReader &reader)
{

	const QXmlStreamAttributes attributes = reader.attributes();
//	for (const QXmlStreamAttribute &attribute : attributes) {
	for (int i = 0; i < attributes.size(); i++) {
		const QXmlStreamAttribute &attribute = attributes.at(i);
		QStringRef name = attribute.name();
		if (name == QLatin1String("startx")) {
			setAttributeStartX(attribute.value().toDouble());
			continue;
		}
		if (name == QLatin1String("starty")) {
			setAttributeStartY(attribute.value().toDouble());
			continue;
		}
		if (name == QLatin1String("endx")) {
			setAttributeEndX(attribute.value().toDouble());
			continue;
		}
		if (name == QLatin1String("endy")) {
			setAttributeEndY(attribute.value().toDouble());
			continue;
		}
		if (name == QLatin1String("centralx")) {
			setAttributeCentralX(attribute.value().toDouble());
			continue;
		}
		if (name == QLatin1String("centraly")) {
			setAttributeCentralY(attribute.value().toDouble());
			continue;
		}
		if (name == QLatin1String("focalx")) {
			setAttributeFocalX(attribute.value().toDouble());
			continue;
		}
		if (name == QLatin1String("focaly")) {
			setAttributeFocalY(attribute.value().toDouble());
			continue;
		}
		if (name == QLatin1String("radius")) {
			setAttributeRadius(attribute.value().toDouble());
			continue;
		}
		if (name == QLatin1String("angle")) {
			setAttributeAngle(attribute.value().toDouble());
			continue;
		}
		if (name == QLatin1String("type")) {
			setAttributeType(attribute.value().toString());
			continue;
		}
		if (name == QLatin1String("spread")) {
			setAttributeSpread(attribute.value().toString());
			continue;
		}
		if (name == QLatin1String("coordinatemode")) {
			setAttributeCoordinateMode(attribute.value().toString());
			continue;
		}
		reader.raiseError(QLatin1String("Unexpected attribute ")/* + name*/);
	}

	for (bool finished = false; !finished && !reader.hasError();) {
		switch (reader.readNext()) {
		case QXmlStreamReader::StartElement : {
			const QString tag = reader.name().toString().toLower();
			if (tag == QLatin1String("gradientstop")) {
				VisDomGradientStop *v = new VisDomGradientStop();
				v->read(reader);
				m_gradientStop.append(v);
				continue;
			}
			reader.raiseError(QLatin1String("Unexpected element ") + tag);
											  }
											  break;
		case QXmlStreamReader::EndElement :
			finished = true;
			break;
		case QXmlStreamReader::Characters :
			if (!reader.isWhitespace())
				m_text.append(reader.text().toString());
			break;
		default :
			break;
		}
	}
}

void VisDomGradient::write(QXmlStreamWriter &writer, const QString &tagName) const
{
	writer.writeStartElement(tagName.isEmpty() ? QString::fromUtf8("gradient") : tagName.toLower());

	if (hasAttributeStartX())
		writer.writeAttribute(QStringLiteral("startx"), QString::number(attributeStartX(), 'f', 15));

	if (hasAttributeStartY())
		writer.writeAttribute(QStringLiteral("starty"), QString::number(attributeStartY(), 'f', 15));

	if (hasAttributeEndX())
		writer.writeAttribute(QStringLiteral("endx"), QString::number(attributeEndX(), 'f', 15));

	if (hasAttributeEndY())
		writer.writeAttribute(QStringLiteral("endy"), QString::number(attributeEndY(), 'f', 15));

	if (hasAttributeCentralX())
		writer.writeAttribute(QStringLiteral("centralx"), QString::number(attributeCentralX(), 'f', 15));

	if (hasAttributeCentralY())
		writer.writeAttribute(QStringLiteral("centraly"), QString::number(attributeCentralY(), 'f', 15));

	if (hasAttributeFocalX())
		writer.writeAttribute(QStringLiteral("focalx"), QString::number(attributeFocalX(), 'f', 15));

	if (hasAttributeFocalY())
		writer.writeAttribute(QStringLiteral("focaly"), QString::number(attributeFocalY(), 'f', 15));

	if (hasAttributeRadius())
		writer.writeAttribute(QStringLiteral("radius"), QString::number(attributeRadius(), 'f', 15));

	if (hasAttributeAngle())
		writer.writeAttribute(QStringLiteral("angle"), QString::number(attributeAngle(), 'f', 15));

	if (hasAttributeType())
		writer.writeAttribute(QStringLiteral("type"), attributeType());

	if (hasAttributeSpread())
		writer.writeAttribute(QStringLiteral("spread"), attributeSpread());

	if (hasAttributeCoordinateMode())
		writer.writeAttribute(QStringLiteral("coordinatemode"), attributeCoordinateMode());

	for (int i = 0; i < m_gradientStop.size(); ++i) {
		VisDomGradientStop* v = m_gradientStop[i];
		v->write(writer, QStringLiteral("gradientstop"));
	}
	if (!m_text.isEmpty())
		writer.writeCharacters(m_text);

	writer.writeEndElement();
}

void VisDomGradient::setElementGradientStop(const QList<VisDomGradientStop*>& a)
{
	m_children |= GradientStop;
	m_gradientStop = a;
}

void VisDomBrush::clear(bool clear_all)
{
	delete m_color;
	delete m_texture;
	delete m_gradient;

	if (clear_all) {
		m_text.clear();
		m_has_attr_brushStyle = false;
	}

	m_kind = Unknown;

	m_color = 0;
	m_texture = 0;
	m_gradient = 0;
}

VisDomBrush::VisDomBrush()
{
	m_kind = Unknown;

	m_has_attr_brushStyle = false;
	m_color = 0;
	m_texture = 0;
	m_gradient = 0;
}

VisDomBrush::~VisDomBrush()
{
	delete m_color;
	delete m_texture;
	delete m_gradient;
}

void VisDomBrush::read(QXmlStreamReader &reader)
{

	const QXmlStreamAttributes attributes = reader.attributes();
//	for (const QXmlStreamAttribute &attribute : attributes) {
	for (int i = 0; i < attributes.size(); i++) {
		const QXmlStreamAttribute &attribute = attributes.at(i);
		QStringRef name = attribute.name();
		if (name == QLatin1String("brushstyle")) {
			setAttributeBrushStyle(attribute.value().toString());
			continue;
		}
		reader.raiseError(QLatin1String("Unexpected attribute ")/* + name*/);
	}

	for (bool finished = false; !finished && !reader.hasError();) {
		switch (reader.readNext()) {
		case QXmlStreamReader::StartElement : {
			const QString tag = reader.name().toString().toLower();
			if (tag == QLatin1String("color")) {
				VisDomColor *v = new VisDomColor();
				v->read(reader);
				setElementColor(v);
				continue;
			}
			if (tag == QLatin1String("texture")) {
				VisDomProperty *v = new VisDomProperty();
				v->read(reader);
				setElementTexture(v);
				continue;
			}
			if (tag == QLatin1String("gradient")) {
				VisDomGradient *v = new VisDomGradient();
				v->read(reader);
				setElementGradient(v);
				continue;
			}
			reader.raiseError(QLatin1String("Unexpected element ") + tag);
											  }
											  break;
		case QXmlStreamReader::EndElement :
			finished = true;
			break;
		case QXmlStreamReader::Characters :
			if (!reader.isWhitespace())
				m_text.append(reader.text().toString());
			break;
		default :
			break;
		}
	}
}

void VisDomBrush::write(QXmlStreamWriter &writer, const QString &tagName) const
{
	writer.writeStartElement(tagName.isEmpty() ? QString::fromUtf8("brush") : tagName.toLower());

	if (hasAttributeBrushStyle())
		writer.writeAttribute(QStringLiteral("brushstyle"), attributeBrushStyle());

	switch (kind()) {
	case Color: {
		VisDomColor* v = elementColor();
		if (v != 0) {
			v->write(writer, QStringLiteral("color"));
		}
		break;
				}
	case Texture: {
		VisDomProperty* v = elementTexture();
		if (v != 0) {
			v->write(writer, QStringLiteral("texture"));
		}
		break;
				  }
	case Gradient: {
		VisDomGradient* v = elementGradient();
		if (v != 0) {
			v->write(writer, QStringLiteral("gradient"));
		}
		break;
				   }
	default:
		break;
	}
	if (!m_text.isEmpty())
		writer.writeCharacters(m_text);

	writer.writeEndElement();
}

VisDomColor* VisDomBrush::takeElementColor()
{
	VisDomColor* a = m_color;
	m_color = 0;
	return a;
}

void VisDomBrush::setElementColor(VisDomColor* a)
{
	clear(false);
	m_kind = Color;
	m_color = a;
}

VisDomProperty* VisDomBrush::takeElementTexture()
{
	VisDomProperty* a = m_texture;
	m_texture = 0;
	return a;
}

void VisDomBrush::setElementTexture(VisDomProperty* a)
{
	clear(false);
	m_kind = Texture;
	m_texture = a;
}

VisDomGradient* VisDomBrush::takeElementGradient()
{
	VisDomGradient* a = m_gradient;
	m_gradient = 0;
	return a;
}

void VisDomBrush::setElementGradient(VisDomGradient* a)
{
	clear(false);
	m_kind = Gradient;
	m_gradient = a;
}

void VisDomColorRole::clear(bool clear_all)
{
	delete m_brush;

	if (clear_all) {
		m_text.clear();
		m_has_attr_role = false;
	}

	m_children = 0;
	m_brush = 0;
}

VisDomColorRole::VisDomColorRole()
{
	m_children = 0;
	m_has_attr_role = false;
	m_brush = 0;
}

VisDomColorRole::~VisDomColorRole()
{
	delete m_brush;
}

void VisDomColorRole::read(QXmlStreamReader &reader)
{

	const QXmlStreamAttributes attributes = reader.attributes();
//	for (const QXmlStreamAttribute &attribute : attributes) {
	for (int i = 0; i < attributes.size(); i++) {
		const QXmlStreamAttribute &attribute = attributes.at(i);
		QStringRef name = attribute.name();
		if (name == QLatin1String("role")) {
			setAttributeRole(attribute.value().toString());
			continue;
		}
		reader.raiseError(QLatin1String("Unexpected attribute ")/* + name*/);
	}

	for (bool finished = false; !finished && !reader.hasError();) {
		switch (reader.readNext()) {
		case QXmlStreamReader::StartElement : {
			const QString tag = reader.name().toString().toLower();
			if (tag == QLatin1String("brush")) {
				VisDomBrush *v = new VisDomBrush();
				v->read(reader);
				setElementBrush(v);
				continue;
			}
			reader.raiseError(QLatin1String("Unexpected element ") + tag);
											  }
											  break;
		case QXmlStreamReader::EndElement :
			finished = true;
			break;
		case QXmlStreamReader::Characters :
			if (!reader.isWhitespace())
				m_text.append(reader.text().toString());
			break;
		default :
			break;
		}
	}
}

void VisDomColorRole::write(QXmlStreamWriter &writer, const QString &tagName) const
{
	writer.writeStartElement(tagName.isEmpty() ? QString::fromUtf8("colorrole") : tagName.toLower());

	if (hasAttributeRole())
		writer.writeAttribute(QStringLiteral("role"), attributeRole());

	if (m_children & Brush) {
		m_brush->write(writer, QStringLiteral("brush"));
	}

	if (!m_text.isEmpty())
		writer.writeCharacters(m_text);

	writer.writeEndElement();
}

VisDomBrush* VisDomColorRole::takeElementBrush()
{
	VisDomBrush* a = m_brush;
	m_brush = 0;
	m_children ^= Brush;
	return a;
}

void VisDomColorRole::setElementBrush(VisDomBrush* a)
{
	delete m_brush;
	m_children |= Brush;
	m_brush = a;
}

void VisDomColorRole::clearElementBrush()
{
	delete m_brush;
	m_brush = 0;
	m_children &= ~Brush;
}

void VisDomColorGroup::clear(bool clear_all)
{
	qDeleteAll(m_colorRole);
	m_colorRole.clear();
	qDeleteAll(m_color);
	m_color.clear();

	if (clear_all) {
		m_text.clear();
	}

	m_children = 0;
}

VisDomColorGroup::VisDomColorGroup()
{
	m_children = 0;
}

VisDomColorGroup::~VisDomColorGroup()
{
	qDeleteAll(m_colorRole);
	m_colorRole.clear();
	qDeleteAll(m_color);
	m_color.clear();
}

void VisDomColorGroup::read(QXmlStreamReader &reader)
{

	for (bool finished = false; !finished && !reader.hasError();) {
		switch (reader.readNext()) {
		case QXmlStreamReader::StartElement : {
			const QString tag = reader.name().toString().toLower();
			if (tag == QLatin1String("colorrole")) {
				VisDomColorRole *v = new VisDomColorRole();
				v->read(reader);
				m_colorRole.append(v);
				continue;
			}
			if (tag == QLatin1String("color")) {
				VisDomColor *v = new VisDomColor();
				v->read(reader);
				m_color.append(v);
				continue;
			}
			reader.raiseError(QLatin1String("Unexpected element ") + tag);
											  }
											  break;
		case QXmlStreamReader::EndElement :
			finished = true;
			break;
		case QXmlStreamReader::Characters :
			if (!reader.isWhitespace())
				m_text.append(reader.text().toString());
			break;
		default :
			break;
		}
	}
}

void VisDomColorGroup::write(QXmlStreamWriter &writer, const QString &tagName) const
{
	writer.writeStartElement(tagName.isEmpty() ? QString::fromUtf8("colorgroup") : tagName.toLower());

	for (int i = 0; i < m_colorRole.size(); ++i) {
		VisDomColorRole* v = m_colorRole[i];
		v->write(writer, QStringLiteral("colorrole"));
	}
	for (int i = 0; i < m_color.size(); ++i) {
		VisDomColor* v = m_color[i];
		v->write(writer, QStringLiteral("color"));
	}
	if (!m_text.isEmpty())
		writer.writeCharacters(m_text);

	writer.writeEndElement();
}

void VisDomColorGroup::setElementColorRole(const QList<VisDomColorRole*>& a)
{
	m_children |= ColorRole;
	m_colorRole = a;
}

void VisDomColorGroup::setElementColor(const QList<VisDomColor*>& a)
{
	m_children |= Color;
	m_color = a;
}

void VisDomPalette::clear(bool clear_all)
{
	delete m_active;
	delete m_inactive;
	delete m_disabled;

	if (clear_all) {
		m_text.clear();
	}

	m_children = 0;
	m_active = 0;
	m_inactive = 0;
	m_disabled = 0;
}

VisDomPalette::VisDomPalette()
{
	m_children = 0;
	m_active = 0;
	m_inactive = 0;
	m_disabled = 0;
}

VisDomPalette::~VisDomPalette()
{
	delete m_active;
	delete m_inactive;
	delete m_disabled;
}

void VisDomPalette::read(QXmlStreamReader &reader)
{

	for (bool finished = false; !finished && !reader.hasError();) {
		switch (reader.readNext()) {
		case QXmlStreamReader::StartElement : {
			const QString tag = reader.name().toString().toLower();
			if (tag == QLatin1String("active")) {
				VisDomColorGroup *v = new VisDomColorGroup();
				v->read(reader);
				setElementActive(v);
				continue;
			}
			if (tag == QLatin1String("inactive")) {
				VisDomColorGroup *v = new VisDomColorGroup();
				v->read(reader);
				setElementInactive(v);
				continue;
			}
			if (tag == QLatin1String("disabled")) {
				VisDomColorGroup *v = new VisDomColorGroup();
				v->read(reader);
				setElementDisabled(v);
				continue;
			}
			reader.raiseError(QLatin1String("Unexpected element ") + tag);
											  }
											  break;
		case QXmlStreamReader::EndElement :
			finished = true;
			break;
		case QXmlStreamReader::Characters :
			if (!reader.isWhitespace())
				m_text.append(reader.text().toString());
			break;
		default :
			break;
		}
	}
}

void VisDomPalette::write(QXmlStreamWriter &writer, const QString &tagName) const
{
	writer.writeStartElement(tagName.isEmpty() ? QString::fromUtf8("palette") : tagName.toLower());

	if (m_children & Active) {
		m_active->write(writer, QStringLiteral("active"));
	}

	if (m_children & Inactive) {
		m_inactive->write(writer, QStringLiteral("inactive"));
	}

	if (m_children & Disabled) {
		m_disabled->write(writer, QStringLiteral("disabled"));
	}

	if (!m_text.isEmpty())
		writer.writeCharacters(m_text);

	writer.writeEndElement();
}

VisDomColorGroup* VisDomPalette::takeElementActive()
{
	VisDomColorGroup* a = m_active;
	m_active = 0;
	m_children ^= Active;
	return a;
}

void VisDomPalette::setElementActive(VisDomColorGroup* a)
{
	delete m_active;
	m_children |= Active;
	m_active = a;
}

VisDomColorGroup* VisDomPalette::takeElementInactive()
{
	VisDomColorGroup* a = m_inactive;
	m_inactive = 0;
	m_children ^= Inactive;
	return a;
}

void VisDomPalette::setElementInactive(VisDomColorGroup* a)
{
	delete m_inactive;
	m_children |= Inactive;
	m_inactive = a;
}

VisDomColorGroup* VisDomPalette::takeElementDisabled()
{
	VisDomColorGroup* a = m_disabled;
	m_disabled = 0;
	m_children ^= Disabled;
	return a;
}

void VisDomPalette::setElementDisabled(VisDomColorGroup* a)
{
	delete m_disabled;
	m_children |= Disabled;
	m_disabled = a;
}

void VisDomPalette::clearElementActive()
{
	delete m_active;
	m_active = 0;
	m_children &= ~Active;
}

void VisDomPalette::clearElementInactive()
{
	delete m_inactive;
	m_inactive = 0;
	m_children &= ~Inactive;
}

void VisDomPalette::clearElementDisabled()
{
	delete m_disabled;
	m_disabled = 0;
	m_children &= ~Disabled;
}

void VisDomFont::clear(bool clear_all)
{

	if (clear_all) {
		m_text.clear();
	}

	m_children = 0;
	m_pointSize = 0;
	m_weight = 0;
	m_italic = false;
	m_bold = false;
	m_underline = false;
	m_strikeOut = false;
	m_antialiasing = false;
	m_kerning = false;
}

VisDomFont::VisDomFont()
{
	m_children = 0;
	m_pointSize = 0;
	m_weight = 0;
	m_italic = false;
	m_bold = false;
	m_underline = false;
	m_strikeOut = false;
	m_antialiasing = false;
	m_kerning = false;
}

VisDomFont::~VisDomFont()
{
}

void VisDomFont::read(QXmlStreamReader &reader)
{

	for (bool finished = false; !finished && !reader.hasError();) {
		switch (reader.readNext()) {
		case QXmlStreamReader::StartElement : {
			const QString tag = reader.name().toString().toLower();
			if (tag == QLatin1String("family")) {
				setElementFamily(reader.readElementText());
				continue;
			}
			if (tag == QLatin1String("pointsize")) {
				setElementPointSize(reader.readElementText().toInt());
				continue;
			}
			if (tag == QLatin1String("weight")) {
				setElementWeight(reader.readElementText().toInt());
				continue;
			}
			if (tag == QLatin1String("italic")) {
				setElementItalic(reader.readElementText() == QLatin1String("true"));
				continue;
			}
			if (tag == QLatin1String("bold")) {
				setElementBold(reader.readElementText() == QLatin1String("true"));
				continue;
			}
			if (tag == QLatin1String("underline")) {
				setElementUnderline(reader.readElementText() == QLatin1String("true"));
				continue;
			}
			if (tag == QLatin1String("strikeout")) {
				setElementStrikeOut(reader.readElementText() == QLatin1String("true"));
				continue;
			}
			if (tag == QLatin1String("antialiasing")) {
				setElementAntialiasing(reader.readElementText() == QLatin1String("true"));
				continue;
			}
			if (tag == QLatin1String("stylestrategy")) {
				setElementStyleStrategy(reader.readElementText());
				continue;
			}
			if (tag == QLatin1String("kerning")) {
				setElementKerning(reader.readElementText() == QLatin1String("true"));
				continue;
			}
			reader.raiseError(QLatin1String("Unexpected element ") + tag);
											  }
											  break;
		case QXmlStreamReader::EndElement :
			finished = true;
			break;
		case QXmlStreamReader::Characters :
			if (!reader.isWhitespace())
				m_text.append(reader.text().toString());
			break;
		default :
			break;
		}
	}
}

void VisDomFont::write(QXmlStreamWriter &writer, const QString &tagName) const
{
	writer.writeStartElement(tagName.isEmpty() ? QString::fromUtf8("font") : tagName.toLower());

	if (m_children & Family) {
		writer.writeTextElement(QStringLiteral("family"), m_family);
	}

	if (m_children & PointSize) {
		writer.writeTextElement(QStringLiteral("pointsize"), QString::number(m_pointSize));
	}

	if (m_children & Weight) {
		writer.writeTextElement(QStringLiteral("weight"), QString::number(m_weight));
	}

	if (m_children & Italic) {
		writer.writeTextElement(QStringLiteral("italic"), (m_italic ? QLatin1String("true") : QLatin1String("false")));
	}

	if (m_children & Bold) {
		writer.writeTextElement(QStringLiteral("bold"), (m_bold ? QLatin1String("true") : QLatin1String("false")));
	}

	if (m_children & Underline) {
		writer.writeTextElement(QStringLiteral("underline"), (m_underline ? QLatin1String("true") : QLatin1String("false")));
	}

	if (m_children & StrikeOut) {
		writer.writeTextElement(QStringLiteral("strikeout"), (m_strikeOut ? QLatin1String("true") : QLatin1String("false")));
	}

	if (m_children & Antialiasing) {
		writer.writeTextElement(QStringLiteral("antialiasing"), (m_antialiasing ? QLatin1String("true") : QLatin1String("false")));
	}

	if (m_children & StyleStrategy) {
		writer.writeTextElement(QStringLiteral("stylestrategy"), m_styleStrategy);
	}

	if (m_children & Kerning) {
		writer.writeTextElement(QStringLiteral("kerning"), (m_kerning ? QLatin1String("true") : QLatin1String("false")));
	}

	if (!m_text.isEmpty())
		writer.writeCharacters(m_text);

	writer.writeEndElement();
}

void VisDomFont::setElementFamily(const QString& a)
{
	m_children |= Family;
	m_family = a;
}

void VisDomFont::setElementPointSize(int a)
{
	m_children |= PointSize;
	m_pointSize = a;
}

void VisDomFont::setElementWeight(int a)
{
	m_children |= Weight;
	m_weight = a;
}

void VisDomFont::setElementItalic(bool a)
{
	m_children |= Italic;
	m_italic = a;
}

void VisDomFont::setElementBold(bool a)
{
	m_children |= Bold;
	m_bold = a;
}

void VisDomFont::setElementUnderline(bool a)
{
	m_children |= Underline;
	m_underline = a;
}

void VisDomFont::setElementStrikeOut(bool a)
{
	m_children |= StrikeOut;
	m_strikeOut = a;
}

void VisDomFont::setElementAntialiasing(bool a)
{
	m_children |= Antialiasing;
	m_antialiasing = a;
}

void VisDomFont::setElementStyleStrategy(const QString& a)
{
	m_children |= StyleStrategy;
	m_styleStrategy = a;
}

void VisDomFont::setElementKerning(bool a)
{
	m_children |= Kerning;
	m_kerning = a;
}

void VisDomFont::clearElementFamily()
{
	m_children &= ~Family;
}

void VisDomFont::clearElementPointSize()
{
	m_children &= ~PointSize;
}

void VisDomFont::clearElementWeight()
{
	m_children &= ~Weight;
}

void VisDomFont::clearElementItalic()
{
	m_children &= ~Italic;
}

void VisDomFont::clearElementBold()
{
	m_children &= ~Bold;
}

void VisDomFont::clearElementUnderline()
{
	m_children &= ~Underline;
}

void VisDomFont::clearElementStrikeOut()
{
	m_children &= ~StrikeOut;
}

void VisDomFont::clearElementAntialiasing()
{
	m_children &= ~Antialiasing;
}

void VisDomFont::clearElementStyleStrategy()
{
	m_children &= ~StyleStrategy;
}

void VisDomFont::clearElementKerning()
{
	m_children &= ~Kerning;
}

void VisDomPoint::clear(bool clear_all)
{

	if (clear_all) {
		m_text.clear();
	}

	m_children = 0;
	m_x = 0;
	m_y = 0;
}

VisDomPoint::VisDomPoint()
{
	m_children = 0;
	m_x = 0;
	m_y = 0;
}

VisDomPoint::~VisDomPoint()
{
}

void VisDomPoint::read(QXmlStreamReader &reader)
{

	for (bool finished = false; !finished && !reader.hasError();) {
		switch (reader.readNext()) {
		case QXmlStreamReader::StartElement : {
			const QString tag = reader.name().toString().toLower();
			if (tag == QLatin1String("x")) {
				setElementX(reader.readElementText().toInt());
				continue;
			}
			if (tag == QLatin1String("y")) {
				setElementY(reader.readElementText().toInt());
				continue;
			}
			reader.raiseError(QLatin1String("Unexpected element ") + tag);
											  }
											  break;
		case QXmlStreamReader::EndElement :
			finished = true;
			break;
		case QXmlStreamReader::Characters :
			if (!reader.isWhitespace())
				m_text.append(reader.text().toString());
			break;
		default :
			break;
		}
	}
}

void VisDomPoint::write(QXmlStreamWriter &writer, const QString &tagName) const
{
	writer.writeStartElement(tagName.isEmpty() ? QString::fromUtf8("point") : tagName.toLower());

	if (m_children & X) {
		writer.writeTextElement(QString(QLatin1Char('x')), QString::number(m_x));
	}

	if (m_children & Y) {
		writer.writeTextElement(QString(QLatin1Char('y')), QString::number(m_y));
	}

	if (!m_text.isEmpty())
		writer.writeCharacters(m_text);

	writer.writeEndElement();
}

void VisDomPoint::setElementX(int a)
{
	m_children |= X;
	m_x = a;
}

void VisDomPoint::setElementY(int a)
{
	m_children |= Y;
	m_y = a;
}

void VisDomPoint::clearElementX()
{
	m_children &= ~X;
}

void VisDomPoint::clearElementY()
{
	m_children &= ~Y;
}

void VisDomRect::clear(bool clear_all)
{

	if (clear_all) {
		m_text.clear();
	}

	m_children = 0;
	m_x = 0;
	m_y = 0;
	m_width = 0;
	m_height = 0;
}

VisDomRect::VisDomRect()
{
	m_children = 0;
	m_x = 0;
	m_y = 0;
	m_width = 0;
	m_height = 0;
}

VisDomRect::~VisDomRect()
{
}

void VisDomRect::read(QXmlStreamReader &reader)
{

	for (bool finished = false; !finished && !reader.hasError();) {
		switch (reader.readNext()) {
		case QXmlStreamReader::StartElement : {
			const QString tag = reader.name().toString().toLower();
			if (tag == QLatin1String("x")) {
				setElementX(reader.readElementText().toInt());
				continue;
			}
			if (tag == QLatin1String("y")) {
				setElementY(reader.readElementText().toInt());
				continue;
			}
			if (tag == QLatin1String("width")) {
				setElementWidth(reader.readElementText().toInt());
				continue;
			}
			if (tag == QLatin1String("height")) {
				setElementHeight(reader.readElementText().toInt());
				continue;
			}
			reader.raiseError(QLatin1String("Unexpected element ") + tag);
											  }
											  break;
		case QXmlStreamReader::EndElement :
			finished = true;
			break;
		case QXmlStreamReader::Characters :
			if (!reader.isWhitespace())
				m_text.append(reader.text().toString());
			break;
		default :
			break;
		}
	}
}

void VisDomRect::write(QXmlStreamWriter &writer, const QString &tagName) const
{
	writer.writeStartElement(tagName.isEmpty() ? QString::fromUtf8("rect") : tagName.toLower());

	if (m_children & X) {
		writer.writeTextElement(QString(QLatin1Char('x')), QString::number(m_x));
	}

	if (m_children & Y) {
		writer.writeTextElement(QString(QLatin1Char('y')), QString::number(m_y));
	}

	if (m_children & Width) {
		writer.writeTextElement(QStringLiteral("width"), QString::number(m_width));
	}

	if (m_children & Height) {
		writer.writeTextElement(QStringLiteral("height"), QString::number(m_height));
	}

	if (!m_text.isEmpty())
		writer.writeCharacters(m_text);

	writer.writeEndElement();
}

void VisDomRect::setElementX(int a)
{
	m_children |= X;
	m_x = a;
}

void VisDomRect::setElementY(int a)
{
	m_children |= Y;
	m_y = a;
}

void VisDomRect::setElementWidth(int a)
{
	m_children |= Width;
	m_width = a;
}

void VisDomRect::setElementHeight(int a)
{
	m_children |= Height;
	m_height = a;
}

void VisDomRect::clearElementX()
{
	m_children &= ~X;
}

void VisDomRect::clearElementY()
{
	m_children &= ~Y;
}

void VisDomRect::clearElementWidth()
{
	m_children &= ~Width;
}

void VisDomRect::clearElementHeight()
{
	m_children &= ~Height;
}

void VisDomLocale::clear(bool clear_all)
{

	if (clear_all) {
		m_text.clear();
		m_has_attr_language = false;
		m_has_attr_country = false;
	}

	m_children = 0;
}

VisDomLocale::VisDomLocale()
{
	m_children = 0;
	m_has_attr_language = false;
	m_has_attr_country = false;
}

VisDomLocale::~VisDomLocale()
{
}

void VisDomLocale::read(QXmlStreamReader &reader)
{

	const QXmlStreamAttributes attributes = reader.attributes();
//	for (const QXmlStreamAttribute &attribute : attributes) {
	for (int i = 0; i < attributes.size(); i++) {
		const QXmlStreamAttribute &attribute = attributes.at(i);
		QStringRef name = attribute.name();
		if (name == QLatin1String("language")) {
			setAttributeLanguage(attribute.value().toString());
			continue;
		}
		if (name == QLatin1String("country")) {
			setAttributeCountry(attribute.value().toString());
			continue;
		}
		reader.raiseError(QLatin1String("Unexpected attribute ") /*+ name*/);
	}

	for (bool finished = false; !finished && !reader.hasError();) {
		switch (reader.readNext()) {
		case QXmlStreamReader::StartElement : {
			const QString tag = reader.name().toString().toLower();
			reader.raiseError(QLatin1String("Unexpected element ") + tag);
											  }
											  break;
		case QXmlStreamReader::EndElement :
			finished = true;
			break;
		case QXmlStreamReader::Characters :
			if (!reader.isWhitespace())
				m_text.append(reader.text().toString());
			break;
		default :
			break;
		}
	}
}

void VisDomLocale::write(QXmlStreamWriter &writer, const QString &tagName) const
{
	writer.writeStartElement(tagName.isEmpty() ? QString::fromUtf8("locale") : tagName.toLower());

	if (hasAttributeLanguage())
		writer.writeAttribute(QStringLiteral("language"), attributeLanguage());

	if (hasAttributeCountry())
		writer.writeAttribute(QStringLiteral("country"), attributeCountry());

	if (!m_text.isEmpty())
		writer.writeCharacters(m_text);

	writer.writeEndElement();
}

void VisDomSizePolicy::clear(bool clear_all)
{

	if (clear_all) {
		m_text.clear();
		m_has_attr_hSizeType = false;
		m_has_attr_vSizeType = false;
	}

	m_children = 0;
	m_hSizeType = 0;
	m_vSizeType = 0;
	m_horStretch = 0;
	m_verStretch = 0;
}

VisDomSizePolicy::VisDomSizePolicy()
{
	m_children = 0;
	m_has_attr_hSizeType = false;
	m_has_attr_vSizeType = false;
	m_hSizeType = 0;
	m_vSizeType = 0;
	m_horStretch = 0;
	m_verStretch = 0;
}

VisDomSizePolicy::~VisDomSizePolicy()
{
}

void VisDomSizePolicy::read(QXmlStreamReader &reader)
{

	const QXmlStreamAttributes attributes = reader.attributes();
//	for (const QXmlStreamAttribute &attribute : attributes) {
	for (int i = 0; i < attributes.size(); i++) {
		const QXmlStreamAttribute &attribute = attributes.at(i);
		QStringRef name = attribute.name();
		if (name == QLatin1String("hsizetype")) {
			setAttributeHSizeType(attribute.value().toString());
			continue;
		}
		if (name == QLatin1String("vsizetype")) {
			setAttributeVSizeType(attribute.value().toString());
			continue;
		}
		reader.raiseError(QLatin1String("Unexpected attribute ")/* + name*/);
	}

	for (bool finished = false; !finished && !reader.hasError();) {
		switch (reader.readNext()) {
		case QXmlStreamReader::StartElement : {
			const QString tag = reader.name().toString().toLower();
			if (tag == QLatin1String("hsizetype")) {
				setElementHSizeType(reader.readElementText().toInt());
				continue;
			}
			if (tag == QLatin1String("vsizetype")) {
				setElementVSizeType(reader.readElementText().toInt());
				continue;
			}
			if (tag == QLatin1String("horstretch")) {
				setElementHorStretch(reader.readElementText().toInt());
				continue;
			}
			if (tag == QLatin1String("verstretch")) {
				setElementVerStretch(reader.readElementText().toInt());
				continue;
			}
			reader.raiseError(QLatin1String("Unexpected element ") + tag);
											  }
											  break;
		case QXmlStreamReader::EndElement :
			finished = true;
			break;
		case QXmlStreamReader::Characters :
			if (!reader.isWhitespace())
				m_text.append(reader.text().toString());
			break;
		default :
			break;
		}
	}
}

void VisDomSizePolicy::write(QXmlStreamWriter &writer, const QString &tagName) const
{
	writer.writeStartElement(tagName.isEmpty() ? QString::fromUtf8("sizepolicy") : tagName.toLower());

	if (hasAttributeHSizeType())
		writer.writeAttribute(QStringLiteral("hsizetype"), attributeHSizeType());

	if (hasAttributeVSizeType())
		writer.writeAttribute(QStringLiteral("vsizetype"), attributeVSizeType());

	if (m_children & HSizeType) {
		writer.writeTextElement(QStringLiteral("hsizetype"), QString::number(m_hSizeType));
	}

	if (m_children & VSizeType) {
		writer.writeTextElement(QStringLiteral("vsizetype"), QString::number(m_vSizeType));
	}

	if (m_children & HorStretch) {
		writer.writeTextElement(QStringLiteral("horstretch"), QString::number(m_horStretch));
	}

	if (m_children & VerStretch) {
		writer.writeTextElement(QStringLiteral("verstretch"), QString::number(m_verStretch));
	}

	if (!m_text.isEmpty())
		writer.writeCharacters(m_text);

	writer.writeEndElement();
}

void VisDomSizePolicy::setElementHSizeType(int a)
{
	m_children |= HSizeType;
	m_hSizeType = a;
}

void VisDomSizePolicy::setElementVSizeType(int a)
{
	m_children |= VSizeType;
	m_vSizeType = a;
}

void VisDomSizePolicy::setElementHorStretch(int a)
{
	m_children |= HorStretch;
	m_horStretch = a;
}

void VisDomSizePolicy::setElementVerStretch(int a)
{
	m_children |= VerStretch;
	m_verStretch = a;
}

void VisDomSizePolicy::clearElementHSizeType()
{
	m_children &= ~HSizeType;
}

void VisDomSizePolicy::clearElementVSizeType()
{
	m_children &= ~VSizeType;
}

void VisDomSizePolicy::clearElementHorStretch()
{
	m_children &= ~HorStretch;
}

void VisDomSizePolicy::clearElementVerStretch()
{
	m_children &= ~VerStretch;
}

void VisDomSize::clear(bool clear_all)
{

	if (clear_all) {
		m_text.clear();
	}

	m_children = 0;
	m_width = 0;
	m_height = 0;
}

VisDomSize::VisDomSize()
{
	m_children = 0;
	m_width = 0;
	m_height = 0;
}

VisDomSize::~VisDomSize()
{
}

void VisDomSize::read(QXmlStreamReader &reader)
{

	for (bool finished = false; !finished && !reader.hasError();) {
		switch (reader.readNext()) {
		case QXmlStreamReader::StartElement : {
			const QString tag = reader.name().toString().toLower();
			if (tag == QLatin1String("width")) {
				setElementWidth(reader.readElementText().toInt());
				continue;
			}
			if (tag == QLatin1String("height")) {
				setElementHeight(reader.readElementText().toInt());
				continue;
			}
			reader.raiseError(QLatin1String("Unexpected element ") + tag);
											  }
											  break;
		case QXmlStreamReader::EndElement :
			finished = true;
			break;
		case QXmlStreamReader::Characters :
			if (!reader.isWhitespace())
				m_text.append(reader.text().toString());
			break;
		default :
			break;
		}
	}
}

void VisDomSize::write(QXmlStreamWriter &writer, const QString &tagName) const
{
	writer.writeStartElement(tagName.isEmpty() ? QString::fromUtf8("size") : tagName.toLower());

	if (m_children & Width) {
		writer.writeTextElement(QStringLiteral("width"), QString::number(m_width));
	}

	if (m_children & Height) {
		writer.writeTextElement(QStringLiteral("height"), QString::number(m_height));
	}

	if (!m_text.isEmpty())
		writer.writeCharacters(m_text);

	writer.writeEndElement();
}

void VisDomSize::setElementWidth(int a)
{
	m_children |= Width;
	m_width = a;
}

void VisDomSize::setElementHeight(int a)
{
	m_children |= Height;
	m_height = a;
}

void VisDomSize::clearElementWidth()
{
	m_children &= ~Width;
}

void VisDomSize::clearElementHeight()
{
	m_children &= ~Height;
}

void VisDomDate::clear(bool clear_all)
{

	if (clear_all) {
		m_text.clear();
	}

	m_children = 0;
	m_year = 0;
	m_month = 0;
	m_day = 0;
}

VisDomDate::VisDomDate()
{
	m_children = 0;
	m_year = 0;
	m_month = 0;
	m_day = 0;
}

VisDomDate::~VisDomDate()
{
}

void VisDomDate::read(QXmlStreamReader &reader)
{

	for (bool finished = false; !finished && !reader.hasError();) {
		switch (reader.readNext()) {
		case QXmlStreamReader::StartElement : {
			const QString tag = reader.name().toString().toLower();
			if (tag == QLatin1String("year")) {
				setElementYear(reader.readElementText().toInt());
				continue;
			}
			if (tag == QLatin1String("month")) {
				setElementMonth(reader.readElementText().toInt());
				continue;
			}
			if (tag == QLatin1String("day")) {
				setElementDay(reader.readElementText().toInt());
				continue;
			}
			reader.raiseError(QLatin1String("Unexpected element ") + tag);
											  }
											  break;
		case QXmlStreamReader::EndElement :
			finished = true;
			break;
		case QXmlStreamReader::Characters :
			if (!reader.isWhitespace())
				m_text.append(reader.text().toString());
			break;
		default :
			break;
		}
	}
}

void VisDomDate::write(QXmlStreamWriter &writer, const QString &tagName) const
{
	writer.writeStartElement(tagName.isEmpty() ? QString::fromUtf8("date") : tagName.toLower());

	if (m_children & Year) {
		writer.writeTextElement(QStringLiteral("year"), QString::number(m_year));
	}

	if (m_children & Month) {
		writer.writeTextElement(QStringLiteral("month"), QString::number(m_month));
	}

	if (m_children & Day) {
		writer.writeTextElement(QStringLiteral("day"), QString::number(m_day));
	}

	if (!m_text.isEmpty())
		writer.writeCharacters(m_text);

	writer.writeEndElement();
}

void VisDomDate::setElementYear(int a)
{
	m_children |= Year;
	m_year = a;
}

void VisDomDate::setElementMonth(int a)
{
	m_children |= Month;
	m_month = a;
}

void VisDomDate::setElementDay(int a)
{
	m_children |= Day;
	m_day = a;
}

void VisDomDate::clearElementYear()
{
	m_children &= ~Year;
}

void VisDomDate::clearElementMonth()
{
	m_children &= ~Month;
}

void VisDomDate::clearElementDay()
{
	m_children &= ~Day;
}

void VisDomTime::clear(bool clear_all)
{

	if (clear_all) {
		m_text.clear();
	}

	m_children = 0;
	m_hour = 0;
	m_minute = 0;
	m_second = 0;
}

VisDomTime::VisDomTime()
{
	m_children = 0;
	m_hour = 0;
	m_minute = 0;
	m_second = 0;
}

VisDomTime::~VisDomTime()
{
}

void VisDomTime::read(QXmlStreamReader &reader)
{

	for (bool finished = false; !finished && !reader.hasError();) {
		switch (reader.readNext()) {
		case QXmlStreamReader::StartElement : {
			const QString tag = reader.name().toString().toLower();
			if (tag == QLatin1String("hour")) {
				setElementHour(reader.readElementText().toInt());
				continue;
			}
			if (tag == QLatin1String("minute")) {
				setElementMinute(reader.readElementText().toInt());
				continue;
			}
			if (tag == QLatin1String("second")) {
				setElementSecond(reader.readElementText().toInt());
				continue;
			}
			reader.raiseError(QLatin1String("Unexpected element ") + tag);
											  }
											  break;
		case QXmlStreamReader::EndElement :
			finished = true;
			break;
		case QXmlStreamReader::Characters :
			if (!reader.isWhitespace())
				m_text.append(reader.text().toString());
			break;
		default :
			break;
		}
	}
}

void VisDomTime::write(QXmlStreamWriter &writer, const QString &tagName) const
{
	writer.writeStartElement(tagName.isEmpty() ? QString::fromUtf8("time") : tagName.toLower());

	if (m_children & Hour) {
		writer.writeTextElement(QStringLiteral("hour"), QString::number(m_hour));
	}

	if (m_children & Minute) {
		writer.writeTextElement(QStringLiteral("minute"), QString::number(m_minute));
	}

	if (m_children & Second) {
		writer.writeTextElement(QStringLiteral("second"), QString::number(m_second));
	}

	if (!m_text.isEmpty())
		writer.writeCharacters(m_text);

	writer.writeEndElement();
}

void VisDomTime::setElementHour(int a)
{
	m_children |= Hour;
	m_hour = a;
}

void VisDomTime::setElementMinute(int a)
{
	m_children |= Minute;
	m_minute = a;
}

void VisDomTime::setElementSecond(int a)
{
	m_children |= Second;
	m_second = a;
}

void VisDomTime::clearElementHour()
{
	m_children &= ~Hour;
}

void VisDomTime::clearElementMinute()
{
	m_children &= ~Minute;
}

void VisDomTime::clearElementSecond()
{
	m_children &= ~Second;
}

void VisDomDateTime::clear(bool clear_all)
{

	if (clear_all) {
		m_text.clear();
	}

	m_children = 0;
	m_hour = 0;
	m_minute = 0;
	m_second = 0;
	m_year = 0;
	m_month = 0;
	m_day = 0;
}

VisDomDateTime::VisDomDateTime()
{
	m_children = 0;
	m_hour = 0;
	m_minute = 0;
	m_second = 0;
	m_year = 0;
	m_month = 0;
	m_day = 0;
}

VisDomDateTime::~VisDomDateTime()
{
}

void VisDomDateTime::read(QXmlStreamReader &reader)
{

	for (bool finished = false; !finished && !reader.hasError();) {
		switch (reader.readNext()) {
		case QXmlStreamReader::StartElement : {
			const QString tag = reader.name().toString().toLower();
			if (tag == QLatin1String("hour")) {
				setElementHour(reader.readElementText().toInt());
				continue;
			}
			if (tag == QLatin1String("minute")) {
				setElementMinute(reader.readElementText().toInt());
				continue;
			}
			if (tag == QLatin1String("second")) {
				setElementSecond(reader.readElementText().toInt());
				continue;
			}
			if (tag == QLatin1String("year")) {
				setElementYear(reader.readElementText().toInt());
				continue;
			}
			if (tag == QLatin1String("month")) {
				setElementMonth(reader.readElementText().toInt());
				continue;
			}
			if (tag == QLatin1String("day")) {
				setElementDay(reader.readElementText().toInt());
				continue;
			}
			reader.raiseError(QLatin1String("Unexpected element ") + tag);
											  }
											  break;
		case QXmlStreamReader::EndElement :
			finished = true;
			break;
		case QXmlStreamReader::Characters :
			if (!reader.isWhitespace())
				m_text.append(reader.text().toString());
			break;
		default :
			break;
		}
	}
}

void VisDomDateTime::write(QXmlStreamWriter &writer, const QString &tagName) const
{
	writer.writeStartElement(tagName.isEmpty() ? QString::fromUtf8("datetime") : tagName.toLower());

	if (m_children & Hour) {
		writer.writeTextElement(QStringLiteral("hour"), QString::number(m_hour));
	}

	if (m_children & Minute) {
		writer.writeTextElement(QStringLiteral("minute"), QString::number(m_minute));
	}

	if (m_children & Second) {
		writer.writeTextElement(QStringLiteral("second"), QString::number(m_second));
	}

	if (m_children & Year) {
		writer.writeTextElement(QStringLiteral("year"), QString::number(m_year));
	}

	if (m_children & Month) {
		writer.writeTextElement(QStringLiteral("month"), QString::number(m_month));
	}

	if (m_children & Day) {
		writer.writeTextElement(QStringLiteral("day"), QString::number(m_day));
	}

	if (!m_text.isEmpty())
		writer.writeCharacters(m_text);

	writer.writeEndElement();
}

void VisDomDateTime::setElementHour(int a)
{
	m_children |= Hour;
	m_hour = a;
}

void VisDomDateTime::setElementMinute(int a)
{
	m_children |= Minute;
	m_minute = a;
}

void VisDomDateTime::setElementSecond(int a)
{
	m_children |= Second;
	m_second = a;
}

void VisDomDateTime::setElementYear(int a)
{
	m_children |= Year;
	m_year = a;
}

void VisDomDateTime::setElementMonth(int a)
{
	m_children |= Month;
	m_month = a;
}

void VisDomDateTime::setElementDay(int a)
{
	m_children |= Day;
	m_day = a;
}

void VisDomDateTime::clearElementHour()
{
	m_children &= ~Hour;
}

void VisDomDateTime::clearElementMinute()
{
	m_children &= ~Minute;
}

void VisDomDateTime::clearElementSecond()
{
	m_children &= ~Second;
}

void VisDomDateTime::clearElementYear()
{
	m_children &= ~Year;
}

void VisDomDateTime::clearElementMonth()
{
	m_children &= ~Month;
}

void VisDomDateTime::clearElementDay()
{
	m_children &= ~Day;
}

void VisDomStringList::clear(bool clear_all)
{
	m_string.clear();

	if (clear_all) {
		m_text.clear();
		m_has_attr_notr = false;
		m_has_attr_comment = false;
		m_has_attr_extraComment = false;
	}

	m_children = 0;
}

VisDomStringList::VisDomStringList()
{
	m_children = 0;
	m_has_attr_notr = false;
	m_has_attr_comment = false;
	m_has_attr_extraComment = false;
}

VisDomStringList::~VisDomStringList()
{
	m_string.clear();
}

void VisDomStringList::read(QXmlStreamReader &reader)
{

	const QXmlStreamAttributes attributes = reader.attributes();
//	for (const QXmlStreamAttribute &attribute : attributes) {
	for (int i = 0; i < attributes.size(); i++) {
		const QXmlStreamAttribute &attribute = attributes.at(i);
		QStringRef name = attribute.name();
		if (name == QLatin1String("notr")) {
			setAttributeNotr(attribute.value().toString());
			continue;
		}
		if (name == QLatin1String("comment")) {
			setAttributeComment(attribute.value().toString());
			continue;
		}
		if (name == QLatin1String("extracomment")) {
			setAttributeExtraComment(attribute.value().toString());
			continue;
		}
		reader.raiseError(QLatin1String("Unexpected attribute ")/* + name*/);
	}

	for (bool finished = false; !finished && !reader.hasError();) {
		switch (reader.readNext()) {
		case QXmlStreamReader::StartElement : {
			const QString tag = reader.name().toString().toLower();
			if (tag == QLatin1String("string")) {
				m_string.append(reader.readElementText());
				continue;
			}
			reader.raiseError(QLatin1String("Unexpected element ") + tag);
											  }
											  break;
		case QXmlStreamReader::EndElement :
			finished = true;
			break;
		case QXmlStreamReader::Characters :
			if (!reader.isWhitespace())
				m_text.append(reader.text().toString());
			break;
		default :
			break;
		}
	}
}

void VisDomStringList::write(QXmlStreamWriter &writer, const QString &tagName) const
{
	writer.writeStartElement(tagName.isEmpty() ? QString::fromUtf8("stringlist") : tagName.toLower());

	if (hasAttributeNotr())
		writer.writeAttribute(QStringLiteral("notr"), attributeNotr());

	if (hasAttributeComment())
		writer.writeAttribute(QStringLiteral("comment"), attributeComment());

	if (hasAttributeExtraComment())
		writer.writeAttribute(QStringLiteral("extracomment"), attributeExtraComment());

	for (int i = 0; i < m_string.size(); ++i) {
		QString v = m_string[i];
		writer.writeTextElement(QStringLiteral("string"), v);
	}
	if (!m_text.isEmpty())
		writer.writeCharacters(m_text);

	writer.writeEndElement();
}

void VisDomStringList::setElementString(const QStringList& a)
{
	m_children |= String;
	m_string = a;
}

void VisDomResourcePixmap::clear(bool clear_all)
{

	if (clear_all) {
		m_text.clear();
		m_has_attr_resource = false;
		m_has_attr_alias = false;
	}

	m_children = 0;
}

VisDomResourcePixmap::VisDomResourcePixmap()
{
	m_children = 0;
	m_has_attr_resource = false;
	m_has_attr_alias = false;
	m_text.clear();
}

VisDomResourcePixmap::~VisDomResourcePixmap()
{
}

void VisDomResourcePixmap::read(QXmlStreamReader &reader)
{

	const QXmlStreamAttributes attributes = reader.attributes();
//	for (const QXmlStreamAttribute &attribute : attributes) {
	for (int i = 0; i < attributes.size(); i++) {
		const QXmlStreamAttribute &attribute = attributes.at(i);
		QStringRef name = attribute.name();
		if (name == QLatin1String("resource")) {
			setAttributeResource(attribute.value().toString());
			continue;
		}
		if (name == QLatin1String("alias")) {
			setAttributeAlias(attribute.value().toString());
			continue;
		}
		reader.raiseError(QLatin1String("Unexpected attribute ")/* + name*/);
	}

	for (bool finished = false; !finished && !reader.hasError();) {
		switch (reader.readNext()) {
		case QXmlStreamReader::StartElement : {
			const QString tag = reader.name().toString().toLower();
			reader.raiseError(QLatin1String("Unexpected element ") + tag);
											  }
											  break;
		case QXmlStreamReader::EndElement :
			finished = true;
			break;
		case QXmlStreamReader::Characters :
			if (!reader.isWhitespace())
				m_text.append(reader.text().toString());
			break;
		default :
			break;
		}
	}
}

void VisDomResourcePixmap::write(QXmlStreamWriter &writer, const QString &tagName) const
{
	writer.writeStartElement(tagName.isEmpty() ? QString::fromUtf8("resourcepixmap") : tagName.toLower());

	if (hasAttributeResource())
		writer.writeAttribute(QStringLiteral("resource"), attributeResource());

	if (hasAttributeAlias())
		writer.writeAttribute(QStringLiteral("alias"), attributeAlias());

	if (!m_text.isEmpty())
		writer.writeCharacters(m_text);

	writer.writeEndElement();
}

void VisDomResourceIcon::clear(bool clear_all)
{
	delete m_normalOff;
	delete m_normalOn;
	delete m_disabledOff;
	delete m_disabledOn;
	delete m_activeOff;
	delete m_activeOn;
	delete m_selectedOff;
	delete m_selectedOn;

	if (clear_all) {
		m_text.clear();
		m_has_attr_theme = false;
		m_has_attr_resource = false;
	}

	m_children = 0;
	m_normalOff = 0;
	m_normalOn = 0;
	m_disabledOff = 0;
	m_disabledOn = 0;
	m_activeOff = 0;
	m_activeOn = 0;
	m_selectedOff = 0;
	m_selectedOn = 0;
}

VisDomResourceIcon::VisDomResourceIcon()
{
	m_children = 0;
	m_has_attr_theme = false;
	m_has_attr_resource = false;
	m_text.clear();
	m_normalOff = 0;
	m_normalOn = 0;
	m_disabledOff = 0;
	m_disabledOn = 0;
	m_activeOff = 0;
	m_activeOn = 0;
	m_selectedOff = 0;
	m_selectedOn = 0;
}

VisDomResourceIcon::~VisDomResourceIcon()
{
	delete m_normalOff;
	delete m_normalOn;
	delete m_disabledOff;
	delete m_disabledOn;
	delete m_activeOff;
	delete m_activeOn;
	delete m_selectedOff;
	delete m_selectedOn;
}

void VisDomResourceIcon::read(QXmlStreamReader &reader)
{

	const QXmlStreamAttributes attributes = reader.attributes();
//	for (const QXmlStreamAttribute &attribute : attributes) {
	for (int i = 0; i < attributes.size(); i++) {
		const QXmlStreamAttribute &attribute = attributes.at(i);
		QStringRef name = attribute.name();
		if (name == QLatin1String("theme")) {
			setAttributeTheme(attribute.value().toString());
			continue;
		}
		if (name == QLatin1String("resource")) {
			setAttributeResource(attribute.value().toString());
			continue;
		}
		reader.raiseError(QLatin1String("Unexpected attribute ")/* + name*/);
	}

	for (bool finished = false; !finished && !reader.hasError();) {
		switch (reader.readNext()) {
		case QXmlStreamReader::StartElement : {
			const QString tag = reader.name().toString().toLower();
			if (tag == QLatin1String("normaloff")) {
				VisDomResourcePixmap *v = new VisDomResourcePixmap();
				v->read(reader);
				setElementNormalOff(v);
				continue;
			}
			if (tag == QLatin1String("normalon")) {
				VisDomResourcePixmap *v = new VisDomResourcePixmap();
				v->read(reader);
				setElementNormalOn(v);
				continue;
			}
			if (tag == QLatin1String("disabledoff")) {
				VisDomResourcePixmap *v = new VisDomResourcePixmap();
				v->read(reader);
				setElementDisabledOff(v);
				continue;
			}
			if (tag == QLatin1String("disabledon")) {
				VisDomResourcePixmap *v = new VisDomResourcePixmap();
				v->read(reader);
				setElementDisabledOn(v);
				continue;
			}
			if (tag == QLatin1String("activeoff")) {
				VisDomResourcePixmap *v = new VisDomResourcePixmap();
				v->read(reader);
				setElementActiveOff(v);
				continue;
			}
			if (tag == QLatin1String("activeon")) {
				VisDomResourcePixmap *v = new VisDomResourcePixmap();
				v->read(reader);
				setElementActiveOn(v);
				continue;
			}
			if (tag == QLatin1String("selectedoff")) {
				VisDomResourcePixmap *v = new VisDomResourcePixmap();
				v->read(reader);
				setElementSelectedOff(v);
				continue;
			}
			if (tag == QLatin1String("selectedon")) {
				VisDomResourcePixmap *v = new VisDomResourcePixmap();
				v->read(reader);
				setElementSelectedOn(v);
				continue;
			}
			reader.raiseError(QLatin1String("Unexpected element ") + tag);
											  }
											  break;
		case QXmlStreamReader::EndElement :
			finished = true;
			break;
		case QXmlStreamReader::Characters :
			if (!reader.isWhitespace())
				m_text.append(reader.text().toString());
			break;
		default :
			break;
		}
	}
}

void VisDomResourceIcon::write(QXmlStreamWriter &writer, const QString &tagName) const
{
	writer.writeStartElement(tagName.isEmpty() ? QString::fromUtf8("resourceicon") : tagName.toLower());

	if (hasAttributeTheme())
		writer.writeAttribute(QStringLiteral("theme"), attributeTheme());

	if (hasAttributeResource())
		writer.writeAttribute(QStringLiteral("resource"), attributeResource());

	if (m_children & NormalOff) {
		m_normalOff->write(writer, QStringLiteral("normaloff"));
	}

	if (m_children & NormalOn) {
		m_normalOn->write(writer, QStringLiteral("normalon"));
	}

	if (m_children & DisabledOff) {
		m_disabledOff->write(writer, QStringLiteral("disabledoff"));
	}

	if (m_children & DisabledOn) {
		m_disabledOn->write(writer, QStringLiteral("disabledon"));
	}

	if (m_children & ActiveOff) {
		m_activeOff->write(writer, QStringLiteral("activeoff"));
	}

	if (m_children & ActiveOn) {
		m_activeOn->write(writer, QStringLiteral("activeon"));
	}

	if (m_children & SelectedOff) {
		m_selectedOff->write(writer, QStringLiteral("selectedoff"));
	}

	if (m_children & SelectedOn) {
		m_selectedOn->write(writer, QStringLiteral("selectedon"));
	}

	if (!m_text.isEmpty())
		writer.writeCharacters(m_text);

	writer.writeEndElement();
}

VisDomResourcePixmap* VisDomResourceIcon::takeElementNormalOff()
{
	VisDomResourcePixmap* a = m_normalOff;
	m_normalOff = 0;
	m_children ^= NormalOff;
	return a;
}

void VisDomResourceIcon::setElementNormalOff(VisDomResourcePixmap* a)
{
	delete m_normalOff;
	m_children |= NormalOff;
	m_normalOff = a;
}

VisDomResourcePixmap* VisDomResourceIcon::takeElementNormalOn()
{
	VisDomResourcePixmap* a = m_normalOn;
	m_normalOn = 0;
	m_children ^= NormalOn;
	return a;
}

void VisDomResourceIcon::setElementNormalOn(VisDomResourcePixmap* a)
{
	delete m_normalOn;
	m_children |= NormalOn;
	m_normalOn = a;
}

VisDomResourcePixmap* VisDomResourceIcon::takeElementDisabledOff()
{
	VisDomResourcePixmap* a = m_disabledOff;
	m_disabledOff = 0;
	m_children ^= DisabledOff;
	return a;
}

void VisDomResourceIcon::setElementDisabledOff(VisDomResourcePixmap* a)
{
	delete m_disabledOff;
	m_children |= DisabledOff;
	m_disabledOff = a;
}

VisDomResourcePixmap* VisDomResourceIcon::takeElementDisabledOn()
{
	VisDomResourcePixmap* a = m_disabledOn;
	m_disabledOn = 0;
	m_children ^= DisabledOn;
	return a;
}

void VisDomResourceIcon::setElementDisabledOn(VisDomResourcePixmap* a)
{
	delete m_disabledOn;
	m_children |= DisabledOn;
	m_disabledOn = a;
}

VisDomResourcePixmap* VisDomResourceIcon::takeElementActiveOff()
{
	VisDomResourcePixmap* a = m_activeOff;
	m_activeOff = 0;
	m_children ^= ActiveOff;
	return a;
}

void VisDomResourceIcon::setElementActiveOff(VisDomResourcePixmap* a)
{
	delete m_activeOff;
	m_children |= ActiveOff;
	m_activeOff = a;
}

VisDomResourcePixmap* VisDomResourceIcon::takeElementActiveOn()
{
	VisDomResourcePixmap* a = m_activeOn;
	m_activeOn = 0;
	m_children ^= ActiveOn;
	return a;
}

void VisDomResourceIcon::setElementActiveOn(VisDomResourcePixmap* a)
{
	delete m_activeOn;
	m_children |= ActiveOn;
	m_activeOn = a;
}

VisDomResourcePixmap* VisDomResourceIcon::takeElementSelectedOff()
{
	VisDomResourcePixmap* a = m_selectedOff;
	m_selectedOff = 0;
	m_children ^= SelectedOff;
	return a;
}

void VisDomResourceIcon::setElementSelectedOff(VisDomResourcePixmap* a)
{
	delete m_selectedOff;
	m_children |= SelectedOff;
	m_selectedOff = a;
}

VisDomResourcePixmap* VisDomResourceIcon::takeElementSelectedOn()
{
	VisDomResourcePixmap* a = m_selectedOn;
	m_selectedOn = 0;
	m_children ^= SelectedOn;
	return a;
}

void VisDomResourceIcon::setElementSelectedOn(VisDomResourcePixmap* a)
{
	delete m_selectedOn;
	m_children |= SelectedOn;
	m_selectedOn = a;
}

void VisDomResourceIcon::clearElementNormalOff()
{
	delete m_normalOff;
	m_normalOff = 0;
	m_children &= ~NormalOff;
}

void VisDomResourceIcon::clearElementNormalOn()
{
	delete m_normalOn;
	m_normalOn = 0;
	m_children &= ~NormalOn;
}

void VisDomResourceIcon::clearElementDisabledOff()
{
	delete m_disabledOff;
	m_disabledOff = 0;
	m_children &= ~DisabledOff;
}

void VisDomResourceIcon::clearElementDisabledOn()
{
	delete m_disabledOn;
	m_disabledOn = 0;
	m_children &= ~DisabledOn;
}

void VisDomResourceIcon::clearElementActiveOff()
{
	delete m_activeOff;
	m_activeOff = 0;
	m_children &= ~ActiveOff;
}

void VisDomResourceIcon::clearElementActiveOn()
{
	delete m_activeOn;
	m_activeOn = 0;
	m_children &= ~ActiveOn;
}

void VisDomResourceIcon::clearElementSelectedOff()
{
	delete m_selectedOff;
	m_selectedOff = 0;
	m_children &= ~SelectedOff;
}

void VisDomResourceIcon::clearElementSelectedOn()
{
	delete m_selectedOn;
	m_selectedOn = 0;
	m_children &= ~SelectedOn;
}

void VisDomString::clear(bool clear_all)
{

	if (clear_all) {
		m_text.clear();
		m_has_attr_notr = false;
		m_has_attr_comment = false;
		m_has_attr_extraComment = false;
	}

	m_children = 0;
}

VisDomString::VisDomString()
{
	m_children = 0;
	m_has_attr_notr = false;
	m_has_attr_comment = false;
	m_has_attr_extraComment = false;
	m_text.clear();
}

VisDomString::~VisDomString()
{
}

void VisDomString::read(QXmlStreamReader &reader)
{

	const QXmlStreamAttributes attributes = reader.attributes();
//	for (const QXmlStreamAttribute &attribute : attributes) {
	for (int i = 0; i < attributes.size(); i++) {
		const QXmlStreamAttribute &attribute = attributes.at(i);
		QStringRef name = attribute.name();
		if (name == QLatin1String("notr")) {
			setAttributeNotr(attribute.value().toString());
			continue;
		}
		if (name == QLatin1String("comment")) {
			setAttributeComment(attribute.value().toString());
			continue;
		}
		if (name == QLatin1String("extracomment")) {
			setAttributeExtraComment(attribute.value().toString());
			continue;
		}
		reader.raiseError(QLatin1String("Unexpected attribute ")/* + name*/);
	}

	for (bool finished = false; !finished && !reader.hasError();) {
		switch (reader.readNext()) {
		case QXmlStreamReader::StartElement : {
			const QString tag = reader.name().toString().toLower();
			reader.raiseError(QLatin1String("Unexpected element ") + tag);
											  }
											  break;
		case QXmlStreamReader::EndElement :
			finished = true;
			break;
		case QXmlStreamReader::Characters :
			if (!reader.isWhitespace())
				m_text.append(reader.text().toString());
			break;
		default :
			break;
		}
	}
}

void VisDomString::write(QXmlStreamWriter &writer, const QString &tagName) const
{
	writer.writeStartElement(tagName.isEmpty() ? QString::fromUtf8("string") : tagName.toLower());

	if (hasAttributeNotr())
		writer.writeAttribute(QStringLiteral("notr"), attributeNotr());

	if (hasAttributeComment())
		writer.writeAttribute(QStringLiteral("comment"), attributeComment());

	if (hasAttributeExtraComment())
		writer.writeAttribute(QStringLiteral("extracomment"), attributeExtraComment());

	if (!m_text.isEmpty())
		writer.writeCharacters(m_text);

	writer.writeEndElement();
}

void VisDomPointF::clear(bool clear_all)
{

	if (clear_all) {
		m_text.clear();
	}

	m_children = 0;
	m_x = 0;
	m_y = 0;
}

VisDomPointF::VisDomPointF()
{
	m_children = 0;
	m_x = 0;
	m_y = 0;
}

VisDomPointF::~VisDomPointF()
{
}

void VisDomPointF::read(QXmlStreamReader &reader)
{

	for (bool finished = false; !finished && !reader.hasError();) {
		switch (reader.readNext()) {
		case QXmlStreamReader::StartElement : {
			const QString tag = reader.name().toString().toLower();
			if (tag == QLatin1String("x")) {
				setElementX(reader.readElementText().toDouble());
				continue;
			}
			if (tag == QLatin1String("y")) {
				setElementY(reader.readElementText().toDouble());
				continue;
			}
			reader.raiseError(QLatin1String("Unexpected element ") + tag);
											  }
											  break;
		case QXmlStreamReader::EndElement :
			finished = true;
			break;
		case QXmlStreamReader::Characters :
			if (!reader.isWhitespace())
				m_text.append(reader.text().toString());
			break;
		default :
			break;
		}
	}
}

void VisDomPointF::write(QXmlStreamWriter &writer, const QString &tagName) const
{
	writer.writeStartElement(tagName.isEmpty() ? QString::fromUtf8("pointf") : tagName.toLower());

	if (m_children & X) {
		writer.writeTextElement(QString(QLatin1Char('x')), QString::number(m_x, 'f', 15));
	}

	if (m_children & Y) {
		writer.writeTextElement(QString(QLatin1Char('y')), QString::number(m_y, 'f', 15));
	}

	if (!m_text.isEmpty())
		writer.writeCharacters(m_text);

	writer.writeEndElement();
}

void VisDomPointF::setElementX(double a)
{
	m_children |= X;
	m_x = a;
}

void VisDomPointF::setElementY(double a)
{
	m_children |= Y;
	m_y = a;
}

void VisDomPointF::clearElementX()
{
	m_children &= ~X;
}

void VisDomPointF::clearElementY()
{
	m_children &= ~Y;
}

void VisDomRectF::clear(bool clear_all)
{

	if (clear_all) {
		m_text.clear();
	}

	m_children = 0;
	m_x = 0;
	m_y = 0;
	m_width = 0;
	m_height = 0;
}

VisDomRectF::VisDomRectF()
{
	m_children = 0;
	m_x = 0;
	m_y = 0;
	m_width = 0;
	m_height = 0;
}

VisDomRectF::~VisDomRectF()
{
}

void VisDomRectF::read(QXmlStreamReader &reader)
{

	for (bool finished = false; !finished && !reader.hasError();) {
		switch (reader.readNext()) {
		case QXmlStreamReader::StartElement : {
			const QString tag = reader.name().toString().toLower();
			if (tag == QLatin1String("x")) {
				setElementX(reader.readElementText().toDouble());
				continue;
			}
			if (tag == QLatin1String("y")) {
				setElementY(reader.readElementText().toDouble());
				continue;
			}
			if (tag == QLatin1String("width")) {
				setElementWidth(reader.readElementText().toDouble());
				continue;
			}
			if (tag == QLatin1String("height")) {
				setElementHeight(reader.readElementText().toDouble());
				continue;
			}
			reader.raiseError(QLatin1String("Unexpected element ") + tag);
											  }
											  break;
		case QXmlStreamReader::EndElement :
			finished = true;
			break;
		case QXmlStreamReader::Characters :
			if (!reader.isWhitespace())
				m_text.append(reader.text().toString());
			break;
		default :
			break;
		}
	}
}

void VisDomRectF::write(QXmlStreamWriter &writer, const QString &tagName) const
{
	writer.writeStartElement(tagName.isEmpty() ? QString::fromUtf8("rectf") : tagName.toLower());

	if (m_children & X) {
		writer.writeTextElement(QString(QLatin1Char('x')), QString::number(m_x, 'f', 15));
	}

	if (m_children & Y) {
		writer.writeTextElement(QString(QLatin1Char('y')), QString::number(m_y, 'f', 15));
	}

	if (m_children & Width) {
		writer.writeTextElement(QStringLiteral("width"), QString::number(m_width, 'f', 15));
	}

	if (m_children & Height) {
		writer.writeTextElement(QStringLiteral("height"), QString::number(m_height, 'f', 15));
	}

	if (!m_text.isEmpty())
		writer.writeCharacters(m_text);

	writer.writeEndElement();
}

void VisDomRectF::setElementX(double a)
{
	m_children |= X;
	m_x = a;
}

void VisDomRectF::setElementY(double a)
{
	m_children |= Y;
	m_y = a;
}

void VisDomRectF::setElementWidth(double a)
{
	m_children |= Width;
	m_width = a;
}

void VisDomRectF::setElementHeight(double a)
{
	m_children |= Height;
	m_height = a;
}

void VisDomRectF::clearElementX()
{
	m_children &= ~X;
}

void VisDomRectF::clearElementY()
{
	m_children &= ~Y;
}

void VisDomRectF::clearElementWidth()
{
	m_children &= ~Width;
}

void VisDomRectF::clearElementHeight()
{
	m_children &= ~Height;
}

void VisDomSizeF::clear(bool clear_all)
{

	if (clear_all) {
		m_text.clear();
	}

	m_children = 0;
	m_width = 0;
	m_height = 0;
}

VisDomSizeF::VisDomSizeF()
{
	m_children = 0;
	m_width = 0;
	m_height = 0;
}

VisDomSizeF::~VisDomSizeF()
{
}

void VisDomSizeF::read(QXmlStreamReader &reader)
{

	for (bool finished = false; !finished && !reader.hasError();) {
		switch (reader.readNext()) {
		case QXmlStreamReader::StartElement : {
			const QString tag = reader.name().toString().toLower();
			if (tag == QLatin1String("width")) {
				setElementWidth(reader.readElementText().toDouble());
				continue;
			}
			if (tag == QLatin1String("height")) {
				setElementHeight(reader.readElementText().toDouble());
				continue;
			}
			reader.raiseError(QLatin1String("Unexpected element ") + tag);
											  }
											  break;
		case QXmlStreamReader::EndElement :
			finished = true;
			break;
		case QXmlStreamReader::Characters :
			if (!reader.isWhitespace())
				m_text.append(reader.text().toString());
			break;
		default :
			break;
		}
	}
}

void VisDomSizeF::write(QXmlStreamWriter &writer, const QString &tagName) const
{
	writer.writeStartElement(tagName.isEmpty() ? QString::fromUtf8("sizef") : tagName.toLower());

	if (m_children & Width) {
		writer.writeTextElement(QStringLiteral("width"), QString::number(m_width, 'f', 15));
	}

	if (m_children & Height) {
		writer.writeTextElement(QStringLiteral("height"), QString::number(m_height, 'f', 15));
	}

	if (!m_text.isEmpty())
		writer.writeCharacters(m_text);

	writer.writeEndElement();
}

void VisDomSizeF::setElementWidth(double a)
{
	m_children |= Width;
	m_width = a;
}

void VisDomSizeF::setElementHeight(double a)
{
	m_children |= Height;
	m_height = a;
}

void VisDomSizeF::clearElementWidth()
{
	m_children &= ~Width;
}

void VisDomSizeF::clearElementHeight()
{
	m_children &= ~Height;
}

void VisDomChar::clear(bool clear_all)
{

	if (clear_all) {
		m_text.clear();
	}

	m_children = 0;
	m_unicode = 0;
}

VisDomChar::VisDomChar()
{
	m_children = 0;
	m_unicode = 0;
}

VisDomChar::~VisDomChar()
{
}

void VisDomChar::read(QXmlStreamReader &reader)
{

	for (bool finished = false; !finished && !reader.hasError();) {
		switch (reader.readNext()) {
		case QXmlStreamReader::StartElement : {
			const QString tag = reader.name().toString().toLower();
			if (tag == QLatin1String("unicode")) {
				setElementUnicode(reader.readElementText().toInt());
				continue;
			}
			reader.raiseError(QLatin1String("Unexpected element ") + tag);
											  }
											  break;
		case QXmlStreamReader::EndElement :
			finished = true;
			break;
		case QXmlStreamReader::Characters :
			if (!reader.isWhitespace())
				m_text.append(reader.text().toString());
			break;
		default :
			break;
		}
	}
}

void VisDomChar::write(QXmlStreamWriter &writer, const QString &tagName) const
{
	writer.writeStartElement(tagName.isEmpty() ? QString::fromUtf8("char") : tagName.toLower());

	if (m_children & Unicode) {
		writer.writeTextElement(QStringLiteral("unicode"), QString::number(m_unicode));
	}

	if (!m_text.isEmpty())
		writer.writeCharacters(m_text);

	writer.writeEndElement();
}

void VisDomChar::setElementUnicode(int a)
{
	m_children |= Unicode;
	m_unicode = a;
}

void VisDomChar::clearElementUnicode()
{
	m_children &= ~Unicode;
}

void VisDomUrl::clear(bool clear_all)
{
	delete m_string;

	if (clear_all) {
		m_text.clear();
	}

	m_children = 0;
	m_string = 0;
}

VisDomUrl::VisDomUrl()
{
	m_children = 0;
	m_string = 0;
}

VisDomUrl::~VisDomUrl()
{
	delete m_string;
}

void VisDomUrl::read(QXmlStreamReader &reader)
{

	for (bool finished = false; !finished && !reader.hasError();) {
		switch (reader.readNext()) {
		case QXmlStreamReader::StartElement : {
			const QString tag = reader.name().toString().toLower();
			if (tag == QLatin1String("string")) {
				VisDomString *v = new VisDomString();
				v->read(reader);
				setElementString(v);
				continue;
			}
			reader.raiseError(QLatin1String("Unexpected element ") + tag);
											  }
											  break;
		case QXmlStreamReader::EndElement :
			finished = true;
			break;
		case QXmlStreamReader::Characters :
			if (!reader.isWhitespace())
				m_text.append(reader.text().toString());
			break;
		default :
			break;
		}
	}
}

void VisDomUrl::write(QXmlStreamWriter &writer, const QString &tagName) const
{
	writer.writeStartElement(tagName.isEmpty() ? QString::fromUtf8("url") : tagName.toLower());

	if (m_children & String) {
		m_string->write(writer, QStringLiteral("string"));
	}

	if (!m_text.isEmpty())
		writer.writeCharacters(m_text);

	writer.writeEndElement();
}

VisDomString* VisDomUrl::takeElementString()
{
	VisDomString* a = m_string;
	m_string = 0;
	m_children ^= String;
	return a;
}

void VisDomUrl::setElementString(VisDomString* a)
{
	delete m_string;
	m_children |= String;
	m_string = a;
}

void VisDomUrl::clearElementString()
{
	delete m_string;
	m_string = 0;
	m_children &= ~String;
}

void VisDomProperty::clear(bool clear_all)
{
	delete m_color;
	delete m_font;
	delete m_iconSet;
	delete m_pixmap;
	delete m_palette;
	delete m_point;
	delete m_rect;
	delete m_locale;
	delete m_sizePolicy;
	delete m_size;
	delete m_string;
	delete m_stringList;
	delete m_date;
	delete m_time;
	delete m_dateTime;
	delete m_pointF;
	delete m_rectF;
	delete m_sizeF;
	delete m_char;
	delete m_url;
	delete m_brush;

	if (clear_all) {
		m_text.clear();
		m_has_attr_name = false;
		m_has_attr_stdset = false;
		m_attr_stdset = 0;
	}

	m_kind = Unknown;

	m_color = 0;
	m_cursor = 0;
	m_font = 0;
	m_iconSet = 0;
	m_pixmap = 0;
	m_palette = 0;
	m_point = 0;
	m_rect = 0;
	m_locale = 0;
	m_sizePolicy = 0;
	m_size = 0;
	m_string = 0;
	m_stringList = 0;
	m_number = 0;
	m_float = 0.0;
	m_double = 0;
	m_date = 0;
	m_time = 0;
	m_dateTime = 0;
	m_pointF = 0;
	m_rectF = 0;
	m_sizeF = 0;
	m_longLong = 0;
	m_char = 0;
	m_url = 0;
	m_UInt = 0;
	m_uLongLong = 0;
	m_brush = 0;
}

VisDomProperty::VisDomProperty()
{
	m_kind = Unknown;

	m_has_attr_name = false;
	m_has_attr_stdset = false;
	m_attr_stdset = 0;
	m_color = 0;
	m_cursor = 0;
	m_font = 0;
	m_iconSet = 0;
	m_pixmap = 0;
	m_palette = 0;
	m_point = 0;
	m_rect = 0;
	m_locale = 0;
	m_sizePolicy = 0;
	m_size = 0;
	m_string = 0;
	m_stringList = 0;
	m_number = 0;
	m_float = 0.0;
	m_double = 0;
	m_date = 0;
	m_time = 0;
	m_dateTime = 0;
	m_pointF = 0;
	m_rectF = 0;
	m_sizeF = 0;
	m_longLong = 0;
	m_char = 0;
	m_url = 0;
	m_UInt = 0;
	m_uLongLong = 0;
	m_brush = 0;
}

VisDomProperty::~VisDomProperty()
{
	delete m_color;
	delete m_font;
	delete m_iconSet;
	delete m_pixmap;
	delete m_palette;
	delete m_point;
	delete m_rect;
	delete m_locale;
	delete m_sizePolicy;
	delete m_size;
	delete m_string;
	delete m_stringList;
	delete m_date;
	delete m_time;
	delete m_dateTime;
	delete m_pointF;
	delete m_rectF;
	delete m_sizeF;
	delete m_char;
	delete m_url;
	delete m_brush;
}

void VisDomProperty::read(QXmlStreamReader &reader)
{

	const QXmlStreamAttributes attributes = reader.attributes();
//	for (const QXmlStreamAttribute &attribute : attributes) {
	for (int i = 0; i < attributes.size(); i++) {
		const QXmlStreamAttribute &attribute = attributes.at(i);
		QStringRef name = attribute.name();
		if (name == QLatin1String("name")) {
			setAttributeName(attribute.value().toString());
			continue;
		}
		if (name == QLatin1String("stdset")) {
			setAttributeStdset(attribute.value().toInt());
			continue;
		}
		reader.raiseError(QLatin1String("Unexpected attribute ")/* + name*/);
	}

	for (bool finished = false; !finished && !reader.hasError();) {
		switch (reader.readNext()) {
		case QXmlStreamReader::StartElement : {
			const QString tag = reader.name().toString().toLower();
			if (tag == QLatin1String("bool")) {
				setElementBool(reader.readElementText());
				continue;
			}
			if (tag == QLatin1String("color")) {
				VisDomColor *v = new VisDomColor();
				v->read(reader);
				setElementColor(v);
				continue;
			}
			if (tag == QLatin1String("cstring")) {
				setElementCstring(reader.readElementText());
				continue;
			}
			if (tag == QLatin1String("cursor")) {
				setElementCursor(reader.readElementText().toInt());
				continue;
			}
			if (tag == QLatin1String("cursorshape")) {
				setElementCursorShape(reader.readElementText());
				continue;
			}
			if (tag == QLatin1String("enum")) {
				setElementEnum(reader.readElementText());
				continue;
			}
			if (tag == QLatin1String("font")) {
				VisDomFont *v = new VisDomFont();
				v->read(reader);
				setElementFont(v);
				continue;
			}
			if (tag == QLatin1String("iconset")) {
				VisDomResourceIcon *v = new VisDomResourceIcon();
				v->read(reader);
				setElementIconSet(v);
				continue;
			}
			if (tag == QLatin1String("pixmap")) {
				VisDomResourcePixmap *v = new VisDomResourcePixmap();
				v->read(reader);
				setElementPixmap(v);
				continue;
			}
			if (tag == QLatin1String("palette")) {
				VisDomPalette *v = new VisDomPalette();
				v->read(reader);
				setElementPalette(v);
				continue;
			}
			if (tag == QLatin1String("point")) {
				VisDomPoint *v = new VisDomPoint();
				v->read(reader);
				setElementPoint(v);
				continue;
			}
			if (tag == QLatin1String("rect")) {
				VisDomRect *v = new VisDomRect();
				v->read(reader);
				setElementRect(v);
				continue;
			}
			if (tag == QLatin1String("set")) {
				setElementSet(reader.readElementText());
				continue;
			}
			if (tag == QLatin1String("locale")) {
				VisDomLocale *v = new VisDomLocale();
				v->read(reader);
				setElementLocale(v);
				continue;
			}
			if (tag == QLatin1String("sizepolicy")) {
				VisDomSizePolicy *v = new VisDomSizePolicy();
				v->read(reader);
				setElementSizePolicy(v);
				continue;
			}
			if (tag == QLatin1String("size")) {
				VisDomSize *v = new VisDomSize();
				v->read(reader);
				setElementSize(v);
				continue;
			}
			if (tag == QLatin1String("string")) {
				VisDomString *v = new VisDomString();
				v->read(reader);
				setElementString(v);
				continue;
			}
			if (tag == QLatin1String("stringlist")) {
				VisDomStringList *v = new VisDomStringList();
				v->read(reader);
				setElementStringList(v);
				continue;
			}
			if (tag == QLatin1String("number")) {
				setElementNumber(reader.readElementText().toInt());
				continue;
			}
			if (tag == QLatin1String("float")) {
				setElementFloat(reader.readElementText().toFloat());
				continue;
			}
			if (tag == QLatin1String("double")) {
				setElementDouble(reader.readElementText().toDouble());
				continue;
			}
			if (tag == QLatin1String("date")) {
				VisDomDate *v = new VisDomDate();
				v->read(reader);
				setElementDate(v);
				continue;
			}
			if (tag == QLatin1String("time")) {
				VisDomTime *v = new VisDomTime();
				v->read(reader);
				setElementTime(v);
				continue;
			}
			if (tag == QLatin1String("datetime")) {
				VisDomDateTime *v = new VisDomDateTime();
				v->read(reader);
				setElementDateTime(v);
				continue;
			}
			if (tag == QLatin1String("pointf")) {
				VisDomPointF *v = new VisDomPointF();
				v->read(reader);
				setElementPointF(v);
				continue;
			}
			if (tag == QLatin1String("rectf")) {
				VisDomRectF *v = new VisDomRectF();
				v->read(reader);
				setElementRectF(v);
				continue;
			}
			if (tag == QLatin1String("sizef")) {
				VisDomSizeF *v = new VisDomSizeF();
				v->read(reader);
				setElementSizeF(v);
				continue;
			}
			if (tag == QLatin1String("longlong")) {
				setElementLongLong(reader.readElementText().toLongLong());
				continue;
			}
			if (tag == QLatin1String("char")) {
				VisDomChar *v = new VisDomChar();
				v->read(reader);
				setElementChar(v);
				continue;
			}
			if (tag == QLatin1String("url")) {
				VisDomUrl *v = new VisDomUrl();
				v->read(reader);
				setElementUrl(v);
				continue;
			}
			if (tag == QLatin1String("uint")) {
				setElementUInt(reader.readElementText().toUInt());
				continue;
			}
			if (tag == QLatin1String("ulonglong")) {
				setElementULongLong(reader.readElementText().toULongLong());
				continue;
			}
			if (tag == QLatin1String("brush")) {
				VisDomBrush *v = new VisDomBrush();
				v->read(reader);
				setElementBrush(v);
				continue;
			}
			reader.raiseError(QLatin1String("Unexpected element ") + tag);
											  }
											  break;
		case QXmlStreamReader::EndElement :
			finished = true;
			break;
		case QXmlStreamReader::Characters :
			if (!reader.isWhitespace())
				m_text.append(reader.text().toString());
			break;
		default :
			break;
		}
	}
}

void VisDomProperty::write(QXmlStreamWriter &writer, const QString &tagName) const
{
	writer.writeStartElement(tagName.isEmpty() ? QString::fromUtf8("property") : tagName.toLower());

	if (hasAttributeName())
		writer.writeAttribute(QStringLiteral("name"), attributeName());

	if (hasAttributeStdset())
		writer.writeAttribute(QStringLiteral("stdset"), QString::number(attributeStdset()));

	switch (kind()) {
	case Bool: {
		writer.writeTextElement(QStringLiteral("bool"), elementBool());
		break;
			   }
	case Color: {
		VisDomColor* v = elementColor();
		if (v != 0) {
			v->write(writer, QStringLiteral("color"));
		}
		break;
				}
	case Cstring: {
		writer.writeTextElement(QStringLiteral("cstring"), elementCstring());
		break;
				  }
	case Cursor: {
		writer.writeTextElement(QStringLiteral("cursor"), QString::number(elementCursor()));
		break;
				 }
	case CursorShape: {
		writer.writeTextElement(QStringLiteral("cursorShape"), elementCursorShape());
		break;
					  }
	case Enum: {
		writer.writeTextElement(QStringLiteral("enum"), elementEnum());
		break;
			   }
	case Font: {
		VisDomFont* v = elementFont();
		if (v != 0) {
			v->write(writer, QStringLiteral("font"));
		}
		break;
			   }
	case IconSet: {
		VisDomResourceIcon* v = elementIconSet();
		if (v != 0) {
			v->write(writer, QStringLiteral("iconset"));
		}
		break;
				  }
	case Pixmap: {
		VisDomResourcePixmap* v = elementPixmap();
		if (v != 0) {
			v->write(writer, QStringLiteral("pixmap"));
		}
		break;
				 }
	case Palette: {
		VisDomPalette* v = elementPalette();
		if (v != 0) {
			v->write(writer, QStringLiteral("palette"));
		}
		break;
				  }
	case Point: {
		VisDomPoint* v = elementPoint();
		if (v != 0) {
			v->write(writer, QStringLiteral("point"));
		}
		break;
				}
	case Rect: {
		VisDomRect* v = elementRect();
		if (v != 0) {
			v->write(writer, QStringLiteral("rect"));
		}
		break;
			   }
	case Set: {
		writer.writeTextElement(QStringLiteral("set"), elementSet());
		break;
			  }
	case Locale: {
		VisDomLocale* v = elementLocale();
		if (v != 0) {
			v->write(writer, QStringLiteral("locale"));
		}
		break;
				 }
	case SizePolicy: {
		VisDomSizePolicy* v = elementSizePolicy();
		if (v != 0) {
			v->write(writer, QStringLiteral("sizepolicy"));
		}
		break;
					 }
	case Size: {
		VisDomSize* v = elementSize();
		if (v != 0) {
			v->write(writer, QStringLiteral("size"));
		}
		break;
			   }
	case String: {
		VisDomString* v = elementString();
		if (v != 0) {
			v->write(writer, QStringLiteral("string"));
		}
		break;
				 }
	case StringList: {
		VisDomStringList* v = elementStringList();
		if (v != 0) {
			v->write(writer, QStringLiteral("stringlist"));
		}
		break;
					 }
	case Number: {
		writer.writeTextElement(QStringLiteral("number"), QString::number(elementNumber()));
		break;
				 }
	case Float: {
		writer.writeTextElement(QStringLiteral("float"), QString::number(elementFloat(), 'f', 8));
		break;
				}
	case Double: {
		writer.writeTextElement(QStringLiteral("double"), QString::number(elementDouble(), 'f', 15));
		break;
				 }
	case Date: {
		VisDomDate* v = elementDate();
		if (v != 0) {
			v->write(writer, QStringLiteral("date"));
		}
		break;
			   }
	case Time: {
		VisDomTime* v = elementTime();
		if (v != 0) {
			v->write(writer, QStringLiteral("time"));
		}
		break;
			   }
	case DateTime: {
		VisDomDateTime* v = elementDateTime();
		if (v != 0) {
			v->write(writer, QStringLiteral("datetime"));
		}
		break;
				   }
	case PointF: {
		VisDomPointF* v = elementPointF();
		if (v != 0) {
			v->write(writer, QStringLiteral("pointf"));
		}
		break;
				 }
	case RectF: {
		VisDomRectF* v = elementRectF();
		if (v != 0) {
			v->write(writer, QStringLiteral("rectf"));
		}
		break;
				}
	case SizeF: {
		VisDomSizeF* v = elementSizeF();
		if (v != 0) {
			v->write(writer, QStringLiteral("sizef"));
		}
		break;
				}
	case LongLong: {
		writer.writeTextElement(QStringLiteral("longLong"), QString::number(elementLongLong()));
		break;
				   }
	case Char: {
		VisDomChar* v = elementChar();
		if (v != 0) {
			v->write(writer, QStringLiteral("char"));
		}
		break;
			   }
	case Url: {
		VisDomUrl* v = elementUrl();
		if (v != 0) {
			v->write(writer, QStringLiteral("url"));
		}
		break;
			  }
	case UInt: {
		writer.writeTextElement(QStringLiteral("UInt"), QString::number(elementUInt()));
		break;
			   }
	case ULongLong: {
		writer.writeTextElement(QStringLiteral("uLongLong"), QString::number(elementULongLong()));
		break;
					}
	case Brush: {
		VisDomBrush* v = elementBrush();
		if (v != 0) {
			v->write(writer, QStringLiteral("brush"));
		}
		break;
				}
	default:
		break;
	}
	if (!m_text.isEmpty())
		writer.writeCharacters(m_text);

	writer.writeEndElement();
}

void VisDomProperty::setElementBool(const QString& a)
{
	clear(false);
	m_kind = Bool;
	m_bool = a;
}

VisDomColor* VisDomProperty::takeElementColor()
{
	VisDomColor* a = m_color;
	m_color = 0;
	return a;
}

void VisDomProperty::setElementColor(VisDomColor* a)
{
	clear(false);
	m_kind = Color;
	m_color = a;
}

void VisDomProperty::setElementCstring(const QString& a)
{
	clear(false);
	m_kind = Cstring;
	m_cstring = a;
}

void VisDomProperty::setElementCursor(int a)
{
	clear(false);
	m_kind = Cursor;
	m_cursor = a;
}

void VisDomProperty::setElementCursorShape(const QString& a)
{
	clear(false);
	m_kind = CursorShape;
	m_cursorShape = a;
}

void VisDomProperty::setElementEnum(const QString& a)
{
	clear(false);
	m_kind = Enum;
	m_enum = a;
}

VisDomFont* VisDomProperty::takeElementFont()
{
	VisDomFont* a = m_font;
	m_font = 0;
	return a;
}

void VisDomProperty::setElementFont(VisDomFont* a)
{
	clear(false);
	m_kind = Font;
	m_font = a;
}

VisDomResourceIcon* VisDomProperty::takeElementIconSet()
{
	VisDomResourceIcon* a = m_iconSet;
	m_iconSet = 0;
	return a;
}

void VisDomProperty::setElementIconSet(VisDomResourceIcon* a)
{
	clear(false);
	m_kind = IconSet;
	m_iconSet = a;
}

VisDomResourcePixmap* VisDomProperty::takeElementPixmap()
{
	VisDomResourcePixmap* a = m_pixmap;
	m_pixmap = 0;
	return a;
}

void VisDomProperty::setElementPixmap(VisDomResourcePixmap* a)
{
	clear(false);
	m_kind = Pixmap;
	m_pixmap = a;
}

VisDomPalette* VisDomProperty::takeElementPalette()
{
	VisDomPalette* a = m_palette;
	m_palette = 0;
	return a;
}

void VisDomProperty::setElementPalette(VisDomPalette* a)
{
	clear(false);
	m_kind = Palette;
	m_palette = a;
}

VisDomPoint* VisDomProperty::takeElementPoint()
{
	VisDomPoint* a = m_point;
	m_point = 0;
	return a;
}

void VisDomProperty::setElementPoint(VisDomPoint* a)
{
	clear(false);
	m_kind = Point;
	m_point = a;
}

VisDomRect* VisDomProperty::takeElementRect()
{
	VisDomRect* a = m_rect;
	m_rect = 0;
	return a;
}

void VisDomProperty::setElementRect(VisDomRect* a)
{
	clear(false);
	m_kind = Rect;
	m_rect = a;
}

void VisDomProperty::setElementSet(const QString& a)
{
	clear(false);
	m_kind = Set;
	m_set = a;
}

VisDomLocale* VisDomProperty::takeElementLocale()
{
	VisDomLocale* a = m_locale;
	m_locale = 0;
	return a;
}

void VisDomProperty::setElementLocale(VisDomLocale* a)
{
	clear(false);
	m_kind = Locale;
	m_locale = a;
}

VisDomSizePolicy* VisDomProperty::takeElementSizePolicy()
{
	VisDomSizePolicy* a = m_sizePolicy;
	m_sizePolicy = 0;
	return a;
}

void VisDomProperty::setElementSizePolicy(VisDomSizePolicy* a)
{
	clear(false);
	m_kind = SizePolicy;
	m_sizePolicy = a;
}

VisDomSize* VisDomProperty::takeElementSize()
{
	VisDomSize* a = m_size;
	m_size = 0;
	return a;
}

void VisDomProperty::setElementSize(VisDomSize* a)
{
	clear(false);
	m_kind = Size;
	m_size = a;
}

VisDomString* VisDomProperty::takeElementString()
{
	VisDomString* a = m_string;
	m_string = 0;
	return a;
}

void VisDomProperty::setElementString(VisDomString* a)
{
	clear(false);
	m_kind = String;
	m_string = a;
}

VisDomStringList* VisDomProperty::takeElementStringList()
{
	VisDomStringList* a = m_stringList;
	m_stringList = 0;
	return a;
}

void VisDomProperty::setElementStringList(VisDomStringList* a)
{
	clear(false);
	m_kind = StringList;
	m_stringList = a;
}

void VisDomProperty::setElementNumber(int a)
{
	clear(false);
	m_kind = Number;
	m_number = a;
}

void VisDomProperty::setElementFloat(float a)
{
	clear(false);
	m_kind = Float;
	m_float = a;
}

void VisDomProperty::setElementDouble(double a)
{
	clear(false);
	m_kind = Double;
	m_double = a;
}

VisDomDate* VisDomProperty::takeElementDate()
{
	VisDomDate* a = m_date;
	m_date = 0;
	return a;
}

void VisDomProperty::setElementDate(VisDomDate* a)
{
	clear(false);
	m_kind = Date;
	m_date = a;
}

VisDomTime* VisDomProperty::takeElementTime()
{
	VisDomTime* a = m_time;
	m_time = 0;
	return a;
}

void VisDomProperty::setElementTime(VisDomTime* a)
{
	clear(false);
	m_kind = Time;
	m_time = a;
}

VisDomDateTime* VisDomProperty::takeElementDateTime()
{
	VisDomDateTime* a = m_dateTime;
	m_dateTime = 0;
	return a;
}

void VisDomProperty::setElementDateTime(VisDomDateTime* a)
{
	clear(false);
	m_kind = DateTime;
	m_dateTime = a;
}

VisDomPointF* VisDomProperty::takeElementPointF()
{
	VisDomPointF* a = m_pointF;
	m_pointF = 0;
	return a;
}

void VisDomProperty::setElementPointF(VisDomPointF* a)
{
	clear(false);
	m_kind = PointF;
	m_pointF = a;
}

VisDomRectF* VisDomProperty::takeElementRectF()
{
	VisDomRectF* a = m_rectF;
	m_rectF = 0;
	return a;
}

void VisDomProperty::setElementRectF(VisDomRectF* a)
{
	clear(false);
	m_kind = RectF;
	m_rectF = a;
}

VisDomSizeF* VisDomProperty::takeElementSizeF()
{
	VisDomSizeF* a = m_sizeF;
	m_sizeF = 0;
	return a;
}

void VisDomProperty::setElementSizeF(VisDomSizeF* a)
{
	clear(false);
	m_kind = SizeF;
	m_sizeF = a;
}

void VisDomProperty::setElementLongLong(qlonglong a)
{
	clear(false);
	m_kind = LongLong;
	m_longLong = a;
}

VisDomChar* VisDomProperty::takeElementChar()
{
	VisDomChar* a = m_char;
	m_char = 0;
	return a;
}

void VisDomProperty::setElementChar(VisDomChar* a)
{
	clear(false);
	m_kind = Char;
	m_char = a;
}

VisDomUrl* VisDomProperty::takeElementUrl()
{
	VisDomUrl* a = m_url;
	m_url = 0;
	return a;
}

void VisDomProperty::setElementUrl(VisDomUrl* a)
{
	clear(false);
	m_kind = Url;
	m_url = a;
}

void VisDomProperty::setElementUInt(uint a)
{
	clear(false);
	m_kind = UInt;
	m_UInt = a;
}

void VisDomProperty::setElementULongLong(qulonglong a)
{
	clear(false);
	m_kind = ULongLong;
	m_uLongLong = a;
}

VisDomBrush* VisDomProperty::takeElementBrush()
{
	VisDomBrush* a = m_brush;
	m_brush = 0;
	return a;
}

void VisDomProperty::setElementBrush(VisDomBrush* a)
{
	clear(false);
	m_kind = Brush;
	m_brush = a;
}

void VisDomConnections::clear(bool clear_all)
{
	qDeleteAll(m_connection);
	m_connection.clear();

	if (clear_all) {
		m_text.clear();
	}

	m_children = 0;
}

VisDomConnections::VisDomConnections()
{
	m_children = 0;
}

VisDomConnections::~VisDomConnections()
{
	qDeleteAll(m_connection);
	m_connection.clear();
}

void VisDomConnections::read(QXmlStreamReader &reader)
{

	for (bool finished = false; !finished && !reader.hasError();) {
		switch (reader.readNext()) {
		case QXmlStreamReader::StartElement : {
			const QString tag = reader.name().toString().toLower();
			if (tag == QLatin1String("connection")) {
				VisDomConnection *v = new VisDomConnection();
				v->read(reader);
				m_connection.append(v);
				continue;
			}
			reader.raiseError(QLatin1String("Unexpected element ") + tag);
											  }
											  break;
		case QXmlStreamReader::EndElement :
			finished = true;
			break;
		case QXmlStreamReader::Characters :
			if (!reader.isWhitespace())
				m_text.append(reader.text().toString());
			break;
		default :
			break;
		}
	}
}

void VisDomConnections::write(QXmlStreamWriter &writer, const QString &tagName) const
{
	writer.writeStartElement(tagName.isEmpty() ? QString::fromUtf8("connections") : tagName.toLower());

	for (int i = 0; i < m_connection.size(); ++i) {
		VisDomConnection* v = m_connection[i];
		v->write(writer, QStringLiteral("connection"));
	}
	if (!m_text.isEmpty())
		writer.writeCharacters(m_text);

	writer.writeEndElement();
}

void VisDomConnections::setElementConnection(const QList<VisDomConnection*>& a)
{
	m_children |= Connection;
	m_connection = a;
}

void VisDomConnection::clear(bool clear_all)
{
	delete m_hints;

	if (clear_all) {
		m_text.clear();
	}

	m_children = 0;
	m_hints = 0;
}

VisDomConnection::VisDomConnection()
{
	m_children = 0;
	m_hints = 0;
}

VisDomConnection::~VisDomConnection()
{
	delete m_hints;
}

void VisDomConnection::read(QXmlStreamReader &reader)
{

	for (bool finished = false; !finished && !reader.hasError();) {
		switch (reader.readNext()) {
		case QXmlStreamReader::StartElement : {
			const QString tag = reader.name().toString().toLower();
			if (tag == QLatin1String("sender")) {
				setElementSender(reader.readElementText());
				continue;
			}
			if (tag == QLatin1String("signal")) {
				setElementSignal(reader.readElementText());
				continue;
			}
			if (tag == QLatin1String("receiver")) {
				setElementReceiver(reader.readElementText());
				continue;
			}
			if (tag == QLatin1String("slot")) {
				setElementSlot(reader.readElementText());
				continue;
			}
			if (tag == QLatin1String("hints")) {
				VisDomConnectionHints *v = new VisDomConnectionHints();
				v->read(reader);
				setElementHints(v);
				continue;
			}
			reader.raiseError(QLatin1String("Unexpected element ") + tag);
											  }
											  break;
		case QXmlStreamReader::EndElement :
			finished = true;
			break;
		case QXmlStreamReader::Characters :
			if (!reader.isWhitespace())
				m_text.append(reader.text().toString());
			break;
		default :
			break;
		}
	}
}

void VisDomConnection::write(QXmlStreamWriter &writer, const QString &tagName) const
{
	writer.writeStartElement(tagName.isEmpty() ? QString::fromUtf8("connection") : tagName.toLower());

	if (m_children & Sender) {
		writer.writeTextElement(QStringLiteral("sender"), m_sender);
	}

	if (m_children & Signal) {
		writer.writeTextElement(QStringLiteral("signal"), m_signal);
	}

	if (m_children & Receiver) {
		writer.writeTextElement(QStringLiteral("receiver"), m_receiver);
	}

	if (m_children & Slot) {
		writer.writeTextElement(QStringLiteral("slot"), m_slot);
	}

	if (m_children & Hints) {
		m_hints->write(writer, QStringLiteral("hints"));
	}

	if (!m_text.isEmpty())
		writer.writeCharacters(m_text);

	writer.writeEndElement();
}

void VisDomConnection::setElementSender(const QString& a)
{
	m_children |= Sender;
	m_sender = a;
}

void VisDomConnection::setElementSignal(const QString& a)
{
	m_children |= Signal;
	m_signal = a;
}

void VisDomConnection::setElementReceiver(const QString& a)
{
	m_children |= Receiver;
	m_receiver = a;
}

void VisDomConnection::setElementSlot(const QString& a)
{
	m_children |= Slot;
	m_slot = a;
}

VisDomConnectionHints* VisDomConnection::takeElementHints()
{
	VisDomConnectionHints* a = m_hints;
	m_hints = 0;
	m_children ^= Hints;
	return a;
}

void VisDomConnection::setElementHints(VisDomConnectionHints* a)
{
	delete m_hints;
	m_children |= Hints;
	m_hints = a;
}

void VisDomConnection::clearElementSender()
{
	m_children &= ~Sender;
}

void VisDomConnection::clearElementSignal()
{
	m_children &= ~Signal;
}

void VisDomConnection::clearElementReceiver()
{
	m_children &= ~Receiver;
}

void VisDomConnection::clearElementSlot()
{
	m_children &= ~Slot;
}

void VisDomConnection::clearElementHints()
{
	delete m_hints;
	m_hints = 0;
	m_children &= ~Hints;
}

void VisDomConnectionHints::clear(bool clear_all)
{
	qDeleteAll(m_hint);
	m_hint.clear();

	if (clear_all) {
		m_text.clear();
	}

	m_children = 0;
}

VisDomConnectionHints::VisDomConnectionHints()
{
	m_children = 0;
}

VisDomConnectionHints::~VisDomConnectionHints()
{
	qDeleteAll(m_hint);
	m_hint.clear();
}

void VisDomConnectionHints::read(QXmlStreamReader &reader)
{

	for (bool finished = false; !finished && !reader.hasError();) {
		switch (reader.readNext()) {
		case QXmlStreamReader::StartElement : {
			const QString tag = reader.name().toString().toLower();
			if (tag == QLatin1String("hint")) {
				VisDomConnectionHint *v = new VisDomConnectionHint();
				v->read(reader);
				m_hint.append(v);
				continue;
			}
			reader.raiseError(QLatin1String("Unexpected element ") + tag);
											  }
											  break;
		case QXmlStreamReader::EndElement :
			finished = true;
			break;
		case QXmlStreamReader::Characters :
			if (!reader.isWhitespace())
				m_text.append(reader.text().toString());
			break;
		default :
			break;
		}
	}
}

void VisDomConnectionHints::write(QXmlStreamWriter &writer, const QString &tagName) const
{
	writer.writeStartElement(tagName.isEmpty() ? QString::fromUtf8("connectionhints") : tagName.toLower());

	for (int i = 0; i < m_hint.size(); ++i) {
		VisDomConnectionHint* v = m_hint[i];
		v->write(writer, QStringLiteral("hint"));
	}
	if (!m_text.isEmpty())
		writer.writeCharacters(m_text);

	writer.writeEndElement();
}

void VisDomConnectionHints::setElementHint(const QList<VisDomConnectionHint*>& a)
{
	m_children |= Hint;
	m_hint = a;
}

void VisDomConnectionHint::clear(bool clear_all)
{

	if (clear_all) {
		m_text.clear();
		m_has_attr_type = false;
	}

	m_children = 0;
	m_x = 0;
	m_y = 0;
}

VisDomConnectionHint::VisDomConnectionHint()
{
	m_children = 0;
	m_has_attr_type = false;
	m_x = 0;
	m_y = 0;
}

VisDomConnectionHint::~VisDomConnectionHint()
{
}

void VisDomConnectionHint::read(QXmlStreamReader &reader)
{

	const QXmlStreamAttributes attributes = reader.attributes();
//	for (const QXmlStreamAttribute &attribute : attributes) {
	for (int i = 0; i < attributes.size(); i++) {
		const QXmlStreamAttribute &attribute = attributes.at(i);
		QStringRef name = attribute.name();
		if (name == QLatin1String("type")) {
			setAttributeType(attribute.value().toString());
			continue;
		}
		reader.raiseError(QLatin1String("Unexpected attribute ")/* + name*/);
	}

	for (bool finished = false; !finished && !reader.hasError();) {
		switch (reader.readNext()) {
		case QXmlStreamReader::StartElement : {
			const QString tag = reader.name().toString().toLower();
			if (tag == QLatin1String("x")) {
				setElementX(reader.readElementText().toInt());
				continue;
			}
			if (tag == QLatin1String("y")) {
				setElementY(reader.readElementText().toInt());
				continue;
			}
			reader.raiseError(QLatin1String("Unexpected element ") + tag);
											  }
											  break;
		case QXmlStreamReader::EndElement :
			finished = true;
			break;
		case QXmlStreamReader::Characters :
			if (!reader.isWhitespace())
				m_text.append(reader.text().toString());
			break;
		default :
			break;
		}
	}
}

void VisDomConnectionHint::write(QXmlStreamWriter &writer, const QString &tagName) const
{
	writer.writeStartElement(tagName.isEmpty() ? QString::fromUtf8("connectionhint") : tagName.toLower());

	if (hasAttributeType())
		writer.writeAttribute(QStringLiteral("type"), attributeType());

	if (m_children & X) {
		writer.writeTextElement(QString(QLatin1Char('x')), QString::number(m_x));
	}

	if (m_children & Y) {
		writer.writeTextElement(QString(QLatin1Char('y')), QString::number(m_y));
	}

	if (!m_text.isEmpty())
		writer.writeCharacters(m_text);

	writer.writeEndElement();
}

void VisDomConnectionHint::setElementX(int a)
{
	m_children |= X;
	m_x = a;
}

void VisDomConnectionHint::setElementY(int a)
{
	m_children |= Y;
	m_y = a;
}

void VisDomConnectionHint::clearElementX()
{
	m_children &= ~X;
}

void VisDomConnectionHint::clearElementY()
{
	m_children &= ~Y;
}

void VisDomScript::clear(bool clear_all)
{

	if (clear_all) {
		m_text.clear();
		m_has_attr_source = false;
		m_has_attr_language = false;
	}

	m_children = 0;
}

VisDomScript::VisDomScript()
{
	m_children = 0;
	m_has_attr_source = false;
	m_has_attr_language = false;
}

VisDomScript::~VisDomScript()
{
}

void VisDomScript::read(QXmlStreamReader &reader)
{

	const QXmlStreamAttributes attributes = reader.attributes();
//	for (const QXmlStreamAttribute &attribute : attributes) {
	for (int i = 0; i < attributes.size(); i++) {
		const QXmlStreamAttribute &attribute = attributes.at(i);
		QStringRef name = attribute.name();
		if (name == QLatin1String("source")) {
			setAttributeSource(attribute.value().toString());
			continue;
		}
		if (name == QLatin1String("language")) {
			setAttributeLanguage(attribute.value().toString());
			continue;
		}
		reader.raiseError(QLatin1String("Unexpected attribute ")/* + name*/);
	}

	for (bool finished = false; !finished && !reader.hasError();) {
		switch (reader.readNext()) {
		case QXmlStreamReader::StartElement : {
			const QString tag = reader.name().toString().toLower();
			reader.raiseError(QLatin1String("Unexpected element ") + tag);
											  }
											  break;
		case QXmlStreamReader::EndElement :
			finished = true;
			break;
		case QXmlStreamReader::Characters :
			if (!reader.isWhitespace())
				m_text.append(reader.text().toString());
			break;
		default :
			break;
		}
	}
}

void VisDomScript::write(QXmlStreamWriter &writer, const QString &tagName) const
{
	writer.writeStartElement(tagName.isEmpty() ? QString::fromUtf8("script") : tagName.toLower());

	if (hasAttributeSource())
		writer.writeAttribute(QStringLiteral("source"), attributeSource());

	if (hasAttributeLanguage())
		writer.writeAttribute(QStringLiteral("language"), attributeLanguage());

	if (!m_text.isEmpty())
		writer.writeCharacters(m_text);

	writer.writeEndElement();
}

void VisDomWidgetData::clear(bool clear_all)
{
	qDeleteAll(m_property);
	m_property.clear();

	if (clear_all) {
		m_text.clear();
	}

	m_children = 0;
}

VisDomWidgetData::VisDomWidgetData()
{
	m_children = 0;
}

VisDomWidgetData::~VisDomWidgetData()
{
	qDeleteAll(m_property);
	m_property.clear();
}

void VisDomWidgetData::read(QXmlStreamReader &reader)
{

	for (bool finished = false; !finished && !reader.hasError();) {
		switch (reader.readNext()) {
		case QXmlStreamReader::StartElement : {
			const QString tag = reader.name().toString().toLower();
			if (tag == QLatin1String("property")) {
				VisDomProperty *v = new VisDomProperty();
				v->read(reader);
				m_property.append(v);
				continue;
			}
			reader.raiseError(QLatin1String("Unexpected element ") + tag);
											  }
											  break;
		case QXmlStreamReader::EndElement :
			finished = true;
			break;
		case QXmlStreamReader::Characters :
			if (!reader.isWhitespace())
				m_text.append(reader.text().toString());
			break;
		default :
			break;
		}
	}
}

void VisDomWidgetData::write(QXmlStreamWriter &writer, const QString &tagName) const
{
	writer.writeStartElement(tagName.isEmpty() ? QString::fromUtf8("widgetdata") : tagName.toLower());

	for (int i = 0; i < m_property.size(); ++i) {
		VisDomProperty* v = m_property[i];
		v->write(writer, QStringLiteral("property"));
	}
	if (!m_text.isEmpty())
		writer.writeCharacters(m_text);

	writer.writeEndElement();
}

void VisDomWidgetData::setElementProperty(const QList<VisDomProperty*>& a)
{
	m_children |= Property;
	m_property = a;
}

void VisDomDesignerData::clear(bool clear_all)
{
	qDeleteAll(m_property);
	m_property.clear();

	if (clear_all) {
		m_text.clear();
	}

	m_children = 0;
}

VisDomDesignerData::VisDomDesignerData()
{
	m_children = 0;
}

VisDomDesignerData::~VisDomDesignerData()
{
	qDeleteAll(m_property);
	m_property.clear();
}

void VisDomDesignerData::read(QXmlStreamReader &reader)
{

	for (bool finished = false; !finished && !reader.hasError();) {
		switch (reader.readNext()) {
		case QXmlStreamReader::StartElement : {
			const QString tag = reader.name().toString().toLower();
			if (tag == QLatin1String("property")) {
				VisDomProperty *v = new VisDomProperty();
				v->read(reader);
				m_property.append(v);
				continue;
			}
			reader.raiseError(QLatin1String("Unexpected element ") + tag);
											  }
											  break;
		case QXmlStreamReader::EndElement :
			finished = true;
			break;
		case QXmlStreamReader::Characters :
			if (!reader.isWhitespace())
				m_text.append(reader.text().toString());
			break;
		default :
			break;
		}
	}
}

void VisDomDesignerData::write(QXmlStreamWriter &writer, const QString &tagName) const
{
	writer.writeStartElement(tagName.isEmpty() ? QString::fromUtf8("designerdata") : tagName.toLower());

	for (int i = 0; i < m_property.size(); ++i) {
		VisDomProperty* v = m_property[i];
		v->write(writer, QStringLiteral("property"));
	}
	if (!m_text.isEmpty())
		writer.writeCharacters(m_text);

	writer.writeEndElement();
}

void VisDomDesignerData::setElementProperty(const QList<VisDomProperty*>& a)
{
	m_children |= Property;
	m_property = a;
}

void VisDomSlots::clear(bool clear_all)
{
	m_signal.clear();
	m_slot.clear();

	if (clear_all) {
		m_text.clear();
	}

	m_children = 0;
}

VisDomSlots::VisDomSlots()
{
	m_children = 0;
}

VisDomSlots::~VisDomSlots()
{
	m_signal.clear();
	m_slot.clear();
}

void VisDomSlots::read(QXmlStreamReader &reader)
{

	for (bool finished = false; !finished && !reader.hasError();) {
		switch (reader.readNext()) {
		case QXmlStreamReader::StartElement : {
			const QString tag = reader.name().toString().toLower();
			if (tag == QLatin1String("signal")) {
				m_signal.append(reader.readElementText());
				continue;
			}
			if (tag == QLatin1String("slot")) {
				m_slot.append(reader.readElementText());
				continue;
			}
			reader.raiseError(QLatin1String("Unexpected element ") + tag);
											  }
											  break;
		case QXmlStreamReader::EndElement :
			finished = true;
			break;
		case QXmlStreamReader::Characters :
			if (!reader.isWhitespace())
				m_text.append(reader.text().toString());
			break;
		default :
			break;
		}
	}
}

void VisDomSlots::write(QXmlStreamWriter &writer, const QString &tagName) const
{
	writer.writeStartElement(tagName.isEmpty() ? QString::fromUtf8("slots") : tagName.toLower());

	for (int i = 0; i < m_signal.size(); ++i) {
		QString v = m_signal[i];
		writer.writeTextElement(QStringLiteral("signal"), v);
	}
	for (int i = 0; i < m_slot.size(); ++i) {
		QString v = m_slot[i];
		writer.writeTextElement(QStringLiteral("slot"), v);
	}
	if (!m_text.isEmpty())
		writer.writeCharacters(m_text);

	writer.writeEndElement();
}

void VisDomSlots::setElementSignal(const QStringList& a)
{
	m_children |= Signal;
	m_signal = a;
}

void VisDomSlots::setElementSlot(const QStringList& a)
{
	m_children |= Slot;
	m_slot = a;
}

void VisDomPropertySpecifications::clear(bool clear_all)
{
	qDeleteAll(m_tooltip);
	m_tooltip.clear();
	qDeleteAll(m_stringpropertyspecification);
	m_stringpropertyspecification.clear();

	if (clear_all) {
		m_text.clear();
	}

	m_children = 0;
}

VisDomPropertySpecifications::VisDomPropertySpecifications()
{
	m_children = 0;
}

VisDomPropertySpecifications::~VisDomPropertySpecifications()
{
	qDeleteAll(m_tooltip);
	m_tooltip.clear();
	qDeleteAll(m_stringpropertyspecification);
	m_stringpropertyspecification.clear();
}

void VisDomPropertySpecifications::read(QXmlStreamReader &reader)
{

	for (bool finished = false; !finished && !reader.hasError();) {
		switch (reader.readNext()) {
		case QXmlStreamReader::StartElement : {
			const QString tag = reader.name().toString().toLower();
			if (tag == QLatin1String("tooltip")) {
				VisDomPropertyToolTip *v = new VisDomPropertyToolTip();
				v->read(reader);
				m_tooltip.append(v);
				continue;
			}
			if (tag == QLatin1String("stringpropertyspecification")) {
				VisDomStringPropertySpecification *v = new VisDomStringPropertySpecification();
				v->read(reader);
				m_stringpropertyspecification.append(v);
				continue;
			}
			reader.raiseError(QLatin1String("Unexpected element ") + tag);
											  }
											  break;
		case QXmlStreamReader::EndElement :
			finished = true;
			break;
		case QXmlStreamReader::Characters :
			if (!reader.isWhitespace())
				m_text.append(reader.text().toString());
			break;
		default :
			break;
		}
	}
}

void VisDomPropertySpecifications::write(QXmlStreamWriter &writer, const QString &tagName) const
{
	writer.writeStartElement(tagName.isEmpty() ? QString::fromUtf8("propertyspecifications") : tagName.toLower());

	for (int i = 0; i < m_tooltip.size(); ++i) {
		VisDomPropertyToolTip* v = m_tooltip[i];
		v->write(writer, QStringLiteral("tooltip"));
	}
	for (int i = 0; i < m_stringpropertyspecification.size(); ++i) {
		VisDomStringPropertySpecification* v = m_stringpropertyspecification[i];
		v->write(writer, QStringLiteral("stringpropertyspecification"));
	}
	if (!m_text.isEmpty())
		writer.writeCharacters(m_text);

	writer.writeEndElement();
}

void VisDomPropertySpecifications::setElementTooltip(const QList<VisDomPropertyToolTip*>& a)
{
	m_children |= Tooltip;
	m_tooltip = a;
}

void VisDomPropertySpecifications::setElementStringpropertyspecification(const QList<VisDomStringPropertySpecification*>& a)
{
	m_children |= Stringpropertyspecification;
	m_stringpropertyspecification = a;
}

void VisDomPropertyToolTip::clear(bool clear_all)
{

	if (clear_all) {
		m_text.clear();
		m_has_attr_name = false;
	}

	m_children = 0;
}

VisDomPropertyToolTip::VisDomPropertyToolTip()
{
	m_children = 0;
	m_has_attr_name = false;
}

VisDomPropertyToolTip::~VisDomPropertyToolTip()
{
}

void VisDomPropertyToolTip::read(QXmlStreamReader &reader)
{

	const QXmlStreamAttributes attributes = reader.attributes();
//	for (const QXmlStreamAttribute &attribute : attributes) {
	for (int i = 0; i < attributes.size(); i++) {
		const QXmlStreamAttribute &attribute = attributes.at(i);
		QStringRef name = attribute.name();
		if (name == QLatin1String("name")) {
			setAttributeName(attribute.value().toString());
			continue;
		}
		reader.raiseError(QLatin1String("Unexpected attribute ")/* + name*/);
	}

	for (bool finished = false; !finished && !reader.hasError();) {
		switch (reader.readNext()) {
		case QXmlStreamReader::StartElement : {
			const QString tag = reader.name().toString().toLower();
			reader.raiseError(QLatin1String("Unexpected element ") + tag);
											  }
											  break;
		case QXmlStreamReader::EndElement :
			finished = true;
			break;
		case QXmlStreamReader::Characters :
			if (!reader.isWhitespace())
				m_text.append(reader.text().toString());
			break;
		default :
			break;
		}
	}
}

void VisDomPropertyToolTip::write(QXmlStreamWriter &writer, const QString &tagName) const
{
	writer.writeStartElement(tagName.isEmpty() ? QString::fromUtf8("propertytooltip") : tagName.toLower());

	if (hasAttributeName())
		writer.writeAttribute(QStringLiteral("name"), attributeName());

	if (!m_text.isEmpty())
		writer.writeCharacters(m_text);

	writer.writeEndElement();
}

void VisDomStringPropertySpecification::clear(bool clear_all)
{

	if (clear_all) {
		m_text.clear();
		m_has_attr_name = false;
		m_has_attr_type = false;
		m_has_attr_notr = false;
	}

	m_children = 0;
}

VisDomStringPropertySpecification::VisDomStringPropertySpecification()
{
	m_children = 0;
	m_has_attr_name = false;
	m_has_attr_type = false;
	m_has_attr_notr = false;
}

VisDomStringPropertySpecification::~VisDomStringPropertySpecification()
{
}

void VisDomStringPropertySpecification::read(QXmlStreamReader &reader)
{

	const QXmlStreamAttributes attributes = reader.attributes();
//	for (const QXmlStreamAttribute &attribute : attributes) {
	for (int i = 0; i < attributes.size(); i++) {
		const QXmlStreamAttribute &attribute = attributes.at(i);
		QStringRef name = attribute.name();
		if (name == QLatin1String("name")) {
			setAttributeName(attribute.value().toString());
			continue;
		}
		if (name == QLatin1String("type")) {
			setAttributeType(attribute.value().toString());
			continue;
		}
		if (name == QLatin1String("notr")) {
			setAttributeNotr(attribute.value().toString());
			continue;
		}
		reader.raiseError(QLatin1String("Unexpected attribute ")/* + name*/);
	}

	for (bool finished = false; !finished && !reader.hasError();) {
		switch (reader.readNext()) {
		case QXmlStreamReader::StartElement : {
			const QString tag = reader.name().toString().toLower();
			reader.raiseError(QLatin1String("Unexpected element ") + tag);
											  }
											  break;
		case QXmlStreamReader::EndElement :
			finished = true;
			break;
		case QXmlStreamReader::Characters :
			if (!reader.isWhitespace())
				m_text.append(reader.text().toString());
			break;
		default :
			break;
		}
	}
}

void VisDomStringPropertySpecification::write(QXmlStreamWriter &writer, const QString &tagName) const
{
	writer.writeStartElement(tagName.isEmpty() ? QString::fromUtf8("stringpropertyspecification") : tagName.toLower());

	if (hasAttributeName())
		writer.writeAttribute(QStringLiteral("name"), attributeName());

	if (hasAttributeType())
		writer.writeAttribute(QStringLiteral("type"), attributeType());

	if (hasAttributeNotr())
		writer.writeAttribute(QStringLiteral("notr"), attributeNotr());

	if (!m_text.isEmpty())
		writer.writeCharacters(m_text);

	writer.writeEndElement();
}

QT_END_NAMESPACE


