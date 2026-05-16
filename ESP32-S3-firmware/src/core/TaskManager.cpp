#include "core/TaskManager.h"

TaskHandle_t TaskManager::networkTaskHandle = nullptr;

bool TaskManager::started = false;

MQTTService* TaskManager::mqttService = nullptr;
OTAService* TaskManager::otaService = nullptr;
GPSSensor* TaskManager::gpsSensor = nullptr;

void TaskManager::begin(
    MQTTService* mqtt,
    OTAService* ota,
    GPSSensor* gps
)
{
    if (started)
    {
        return;
    }

    mqttService = mqtt;
    otaService = ota;
    gpsSensor = gps;

    started = true;

    BaseType_t result = xTaskCreatePinnedToCore(
        networkTask,
        "NetworkTask",
        8192,
        nullptr,
        2,
        &networkTaskHandle,
        0
    );

    if (result == pdPASS)
    {
        Serial.println("[TaskManager] Network task started on Core 0");
    }
    else
    {
        Serial.println("[TaskManager] Failed to start Network task");
    }
}

void TaskManager::update()
{
}

void TaskManager::networkTask(void* parameter)
{
    Serial.println("[TaskManager] Network task running");

    while (true)
    {
        if (otaService != nullptr)
        {
            otaService->update();
        }

        if (mqttService != nullptr)
        {
            mqttService->update();
        }

        if (gpsSensor != nullptr)
        {
            gpsSensor->update();
        }

        vTaskDelay(pdMS_TO_TICKS(5));
    }
}