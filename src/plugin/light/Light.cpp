#include "Light.hpp"

plugin::light::Light::Light(lightType type, plugin::light::LightModel::Type model) 
{ 
	_type = type;
    _model.setLightModel(model);
    updateLightType();
    id = _nextId;
    _nextId++;
}

glm::vec3 plugin::light::Light::getLightDirection() 
{ 
    glm::vec3 p = {0, 0, 0};

    switch (_type)
    {
    case plugin::light::Light::lightType::AMBIENT: break;
    case plugin::light::Light::lightType::DIRECTIONAL: p = directional.direction; break;
    case plugin::light::Light::lightType::POINT_LIGHT: break;
    case plugin::light::Light::lightType::SPOT: p = spot.direction; break;
    default: break;
    }

    return p;
}

glm::vec3 plugin::light::Light::getLightColor() { return ambient.color; }

float plugin::light::Light::getCutOffAngle()
{ 
    if (_type == plugin::light::Light::lightType::SPOT)
    {
        return spot.cutoffAngle;
    }

    return -1.0f;
}

float plugin::light::Light::getIntensity()
{ 
    float intensity = -1.0f;

    switch (_type)
    {
    case plugin::light::Light::lightType::AMBIENT: break;
    case plugin::light::Light::lightType::DIRECTIONAL: break;
    case plugin::light::Light::lightType::POINT_LIGHT: intensity = point.intensity; break;
    case plugin::light::Light::lightType::SPOT: intensity = spot.intensity; break;
    default: break;
    }

    return intensity;
}

plugin::light::LightModel::Type plugin::light::Light::getLightModel() { return _model.getLightModel(); }

void plugin::light::Light::setLightPosition(glm::vec3 lightPosition)
{ 
	_model.setLightPosition(lightPosition); 

	switch (_type)
	{
    case plugin::light::Light::lightType::AMBIENT: break;
    case plugin::light::Light::lightType::DIRECTIONAL: break;
    case plugin::light::Light::lightType::POINT_LIGHT: point.position = lightPosition; break;
    case plugin::light::Light::lightType::SPOT: spot.position = lightPosition; break;
    default: break;
	}
}

void plugin::light::Light::setLightType(lightType type)
{ 
	if (type == plugin::light::Light::lightType::AMBIENT)
	{
        if (_model.getLightModel() == plugin::light::LightModel::Type::Phong || 
			_model.getLightModel() == plugin::light::LightModel::Type::BlinnPhong)
		{
            std::cerr << "Une lumiere ambiante ne produit pas de reflexion speculaire. Il est inutile d'appliquer "
                         "Phong ou Blinn-Phong."
                      << std::endl;
            _model.setLightModel(plugin::light::LightModel::Type::Lambert);
		}
	}

	else
	{
        _type = type;
	}

	updateLightType();
}

void plugin::light::Light::setLightDirection(glm::vec3 lightDirection)
{
    switch (_type)
    {
    case plugin::light::Light::lightType::AMBIENT: break;
    case plugin::light::Light::lightType::DIRECTIONAL: directional.direction = lightDirection;
    case plugin::light::Light::lightType::POINT_LIGHT: break;
    case plugin::light::Light::lightType::SPOT: spot.position = lightDirection;
    default: break;
    }
}

void plugin::light::Light::setLightColor(glm::vec3 lightColor)
{ 
    ambient.color = lightColor;
    directional.color = lightColor;
    point.color = lightColor;
    spot.color = lightColor;
}

void plugin::light::Light::setLightAngle(float angle)
{
    switch (_type)
    {
    case plugin::light::Light::lightType::AMBIENT: break;
    case plugin::light::Light::lightType::DIRECTIONAL: break;
    case plugin::light::Light::lightType::POINT_LIGHT: break;
    case plugin::light::Light::lightType::SPOT: spot.cutoffAngle = angle;
    default: break;
    }
}

void plugin::light::Light::setLightIntensity(float intensity)
{
    switch (_type)
    {
    case plugin::light::Light::lightType::AMBIENT: break;
    case plugin::light::Light::lightType::DIRECTIONAL: break;
    case plugin::light::Light::lightType::POINT_LIGHT: break;
    case plugin::light::Light::lightType::SPOT: spot.intensity = intensity; break;
    default: break;
    }
}

void plugin::light::Light::setLightModel(plugin::light::LightModel::Type model)
{ 
	if (_type == plugin::light::Light::lightType::AMBIENT)
	{
        if (_model.getLightModel() == plugin::light::LightModel::Type::Phong ||
            _model.getLightModel() == plugin::light::LightModel::Type::BlinnPhong)
		{
            std::cerr << "Une lumiere ambiante ne produit pas de reflexion speculaire. Il est inutile d'appliquer "
                         "Phong ou Blinn-Phong."
                      << std::endl;
            _model.setLightModel(plugin::light::LightModel::Type::Lambert);
		}
	}

	else
	{
        _model.setLightModel(model);
	}
}

void plugin::light::Light::apply()
{ 
	_model.begin();
    ptrType->apply();
}

void plugin::light::Light::close()
{
    _model.end();
    ptrType->close();
}

void plugin::light::Light::updateLightType()
{ 
	switch (_type)
    {
    case plugin::light::Light::lightType::AMBIENT: ptrType = &ambient; break;
    case plugin::light::Light::lightType::POINT_LIGHT: ptrType = &point; break;
    case plugin::light::Light::lightType::DIRECTIONAL: ptrType = &directional; break;
    case plugin::light::Light::lightType::SPOT: ptrType = &spot; break;
        default: break;
    }
}
