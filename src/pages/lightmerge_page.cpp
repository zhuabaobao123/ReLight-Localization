#include "pages/lightmerge_page.h"
#include "../ticker.h"
#include "../global.h"
#include "../ini.h"

using namespace UI; 

void __stdcall RenderLightMergeMenu() {

    if (ImGuiMCP::BeginChild("Light Merge", ImGuiMCP::ImVec2(0, 340), true,
        ImGuiMCP::ImGuiWindowFlags_NoScrollbar))
    {
        ImGuiMCP::PushStyleColor(ImGuiMCP::ImGuiCol_Text, ImGuiMCP::ImVec4{ 1.0f, 0.85f, 0.4f, 1.0f });

        ImGuiMCP::Text(QLT("Light Merge"));

        ImGuiMCP::PopStyleColor();

        ImGuiMCP::SameLine();

        bool saveINIClicked = ImGuiMCP::Button(QLT("Save INI"));

        ImGuiMCP::ImVec2 rectMax = ImGuiMCP::GetItemRectMax();
        ImGuiMCP::ImVec2 rectMin = ImGuiMCP::GetItemRectMin();
        ImGuiMCP::ImVec2 winPos = ImGuiMCP::GetWindowPos();

        float iconX = (rectMax.x - winPos.x) + 10.0f;
        float iconY = (rectMin.y - winPos.y) + 4.0f;
        if (saveINIClicked) {
            bool ok = false;
            saveINIButton.set(buttonState::Working);
            ok = ini::saveSettingsToIni();
            saveINIButton.set(ok ? buttonState::Success : buttonState::Fail, 2.0f);
        }
        renderDone(saveINIButton, iconX, iconY);

        ImGuiMCP::SameLine();

        ImGuiMCP::Text(QLT("(This only works with relight lights that use relight flags)"));

        ImGuiMCP::Spacing();


        ImGuiMCP::ImVec2 avail = ImGuiMCP::GetContentRegionAvail();

        ImGuiMCP::Columns(2, "Bound", false);
        ImGuiMCP::SetColumnWidth(0, avail.x * 0.5f);
        ImGuiMCP::SetColumnWidth(1, avail.x * 0.5f);

        float colWidth = avail.x * 0.25f;
        ImGuiMCP::PushItemWidth(colWidth);

        if (ImGuiMCP::Checkbox(QLT("Enable Light Merging"), &globals::enableLightMerging)) {
        }

        if (ImGuiMCP::IsItemHovered()) {
            ImGuiMCP::SetTooltip(QLT("Enable / Disable light merging"));
        }


        if (ImGuiMCP::Checkbox(QLT("Enable Shadow Light Merging"), &globals::enableShadowLightMerging)) {
        }

        if (ImGuiMCP::IsItemHovered()) {
            ImGuiMCP::BeginTooltip();
            ImGuiMCP::PushStyleColor(ImGuiMCP::ImGuiCol_Text, ImGuiMCP::ImVec4(1.0f, 0.2f, 0.2f, 1.0f));
            ImGuiMCP::Text(QLT("WARNING: Disabling shadow light merging can cause you to exceed skyrims 4 shadow light limit per area"));
            ImGuiMCP::Text(QLT("Enable / Disable light merging"));
            ImGuiMCP::PopStyleColor();
            ImGuiMCP::EndTooltip();
        }

        ImGuiMCP::SliderInt(QLT("Max lights to merge"), &globals::lightMergeMaxLights, 0, 25);

        if (ImGuiMCP::IsItemHovered()) {
            ImGuiMCP::SetTooltip(QLT("will merge no more then this amount of lights during 1 merge"));
        }

        ImGuiMCP::SliderFloat(QLT("Distance to light merge"), &globals::lightMergeDistance, 0, 300);

        if (ImGuiMCP::IsItemHovered()) {
            ImGuiMCP::SetTooltip(QLT("Refs placed further apart will not merge"));
        }

        ImGuiMCP::SliderFloat(QLT("Merge distance increased"), &globals::lightMergeSeekingDistance, 0, 300);

        if (ImGuiMCP::IsItemHovered()) {
            ImGuiMCP::SetTooltip(QLT("Used for configs with the IncreasedMergeDistance flag"));
        }
        ImGuiMCP::SliderFloat(QLT("Merge distance shadow light"), &globals::shadowLightMergeDistance, 0, 300);

        if (ImGuiMCP::IsItemHovered()) {
            ImGuiMCP::SetTooltip(QLT("Don't turn this down its for fire meshes stacked on top of each other"));
        }

        ImGuiMCP::NextColumn();
        ImGuiMCP::PushItemWidth(colWidth);


        ImGuiMCP::SliderFloat(QLT("Z distance allowed to merge"), &globals::fMaxZDiffToMerge, 0, 300);

        if (ImGuiMCP::IsItemHovered()) {
            ImGuiMCP::SetTooltip(QLT("If z distance is greater, will not merge"));
        }

        ImGuiMCP::SliderFloat(QLT("Z distance Increased"), &globals::fMaxZDiffToMergeIncreased, 0, 300);

        if (ImGuiMCP::IsItemHovered()) {
            ImGuiMCP::SetTooltip(QLT("For configs with the IncreasedMergeDistance flag"));
        }

        ImGuiMCP::SliderFloat(QLT("Fade Boost per Merge"), &globals::lightFadePerMerge, 0.0f, 1.0f);
        if (ImGuiMCP::IsItemHovered())
            ImGuiMCP::SetTooltip(QLT("Increase in fade per additional merged light."));

        ImGuiMCP::SliderFloat(QLT("Radius Boost per Merge"), &globals::lightRadiusPerMerge, 0.0f, 1.0f);
        if (ImGuiMCP::IsItemHovered())
            ImGuiMCP::SetTooltip(QLT("Increase in radius per additional merged light."));

        ImGuiMCP::SliderFloat(QLT("Max Fade Multiplier"), &globals::lightFadeMax, 1.0f, 5.0f);
        if (ImGuiMCP::IsItemHovered())
            ImGuiMCP::SetTooltip(QLT("Max fade mult after merging."));

        ImGuiMCP::SliderFloat(QLT("Max Radius Multiplier"), &globals::lightRadiusMax, 1.0f, 5.0f);
        if (ImGuiMCP::IsItemHovered())
            ImGuiMCP::SetTooltip(QLT("Max radius mult after merging."));

        ImGuiMCP::PopItemWidth();
    }

    ImGuiMCP::EndChild();
}
