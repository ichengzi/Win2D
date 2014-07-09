// Copyright (c) Microsoft Corporation. All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License"); you may
// not use these files except in compliance with the License. You may obtain
// a copy of the License at http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
// WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
// License for the specific language governing permissions and limitations
// under the License.

#pragma once

#include "ClosablePtr.h"

namespace canvas
{
    using namespace ABI::Microsoft::Graphics::Canvas;
    using namespace ABI::Windows::Foundation;
    using namespace Microsoft::WRL;

    class ICanvasDrawingSessionAdapter
    {
    public:
        virtual ~ICanvasDrawingSessionAdapter() = default;
        virtual void EndDraw() = 0;
    };

    class CanvasDrawingSessionManager;
    class CanvasDrawingSession;

    class CanvasDrawingSessionFactory
        : public ActivationFactory<ICanvasDrawingSessionStatics, CloakedIid<ICanvasFactoryNative>>,
          public FactoryWithResourceManager<CanvasDrawingSessionFactory, CanvasDrawingSessionManager>
    {
        InspectableClassStatic(RuntimeClass_Microsoft_Graphics_Canvas_CanvasDrawingSession, BaseTrust);

    public:
        //
        // ICanvasFactoryNative
        //

        IFACEMETHOD(GetOrCreate)(
            IUnknown* resource,
            IInspectable** wrapper) override;        
    };

    struct CanvasDrawingSessionTraits
    {
        typedef ID2D1DeviceContext1 resource_t;
        typedef CanvasDrawingSession wrapper_t;
        typedef ICanvasDrawingSession wrapper_interface_t;
        typedef CanvasDrawingSessionManager manager_t;
    };

    class CanvasDrawingSession : RESOURCE_WRAPPER_RUNTIME_CLASS(
        CanvasDrawingSessionTraits)
    {
        InspectableClass(RuntimeClass_Microsoft_Graphics_Canvas_CanvasDrawingSession, BaseTrust);

        std::shared_ptr<ICanvasDrawingSessionAdapter> m_adapter;

    public:
        CanvasDrawingSession(
            std::shared_ptr<CanvasDrawingSessionManager> manager,
            ID2D1DeviceContext1* deviceContext,
            std::shared_ptr<ICanvasDrawingSessionAdapter> drawingSessionAdapter);

        virtual ~CanvasDrawingSession();

        // IClosable

        IFACEMETHOD(Close)() override;

        // ICanvasDrawingSession

        IFACEMETHOD(Clear)(
            ABI::Windows::UI::Color color) override;

        IFACEMETHOD(DrawLine)(
            ABI::Windows::Foundation::Point point0,
            ABI::Windows::Foundation::Point point1,
            ICanvasBrush* brush) override;

        IFACEMETHOD(DrawLineWithStrokeWidth)(
            ABI::Windows::Foundation::Point point0,
            ABI::Windows::Foundation::Point point1,
            ICanvasBrush* brush,
            float strokeWidth) override;

        IFACEMETHOD(DrawLineWithStrokeWidthAndStrokeStyle)(
            ABI::Windows::Foundation::Point point0,
            ABI::Windows::Foundation::Point point1,
            ICanvasBrush* brush,
            float strokeWidth,
            ICanvasStrokeStyle* strokeStyle) override;

        IFACEMETHOD(DrawRectangle)(
            ABI::Windows::Foundation::Rect rect,
            ICanvasBrush* brush) override;

        IFACEMETHOD(DrawRectangleWithStrokeWidth)(
            ABI::Windows::Foundation::Rect rect,
            ICanvasBrush* brush,
            float strokeWidth) override;

        IFACEMETHOD(DrawRectangleWithStrokeWidthAndStrokeStyle)(
            ABI::Windows::Foundation::Rect rect,
            ICanvasBrush* brush,
            float strokeWidth,
            ICanvasStrokeStyle* strokeStyle) override;

        IFACEMETHOD(FillRectangle)(
            ABI::Windows::Foundation::Rect rect,
            ICanvasBrush* brush) override;

        IFACEMETHOD(DrawRoundedRectangle)(
            CanvasRoundedRectangle roundedRectangle,
            ICanvasBrush* brush) override;

        IFACEMETHOD(DrawRoundedRectangleWithStrokeWidth)(
            CanvasRoundedRectangle roundedRectangle,
            ICanvasBrush* brush,
            float strokeWidth) override;

        IFACEMETHOD(DrawRoundedRectangleWithStrokeWidthAndStrokeStyle)(
            CanvasRoundedRectangle roundedRectangle,
            ICanvasBrush* brush,
            float strokeWidth,
            ICanvasStrokeStyle* strokeStyle) override;

        IFACEMETHOD(FillRoundedRectangle)(
            CanvasRoundedRectangle roundedRectangle,
            ICanvasBrush* brush) override;

        IFACEMETHOD(DrawEllipse)(
            CanvasEllipse ellipse,
            ICanvasBrush* brush) override;

        IFACEMETHOD(DrawEllipseWithStrokeWidth)(
            CanvasEllipse ellipse,
            ICanvasBrush* brush,
            float strokeWidth) override;

        IFACEMETHOD(DrawEllipseWithStrokeWidthAndStrokeStyle)(
            CanvasEllipse ellipse,
            ICanvasBrush* brush,
            float strokeWidth,
            ICanvasStrokeStyle* strokeStyle) override;

        IFACEMETHOD(FillEllipse)(
            CanvasEllipse ellipse,
            ICanvasBrush* brush) override;
    };


    class CanvasDrawingSessionManager : public ResourceManager<CanvasDrawingSessionTraits>
    {
        std::shared_ptr<ICanvasDrawingSessionAdapter> m_adapter;

    public:
        CanvasDrawingSessionManager();

        ComPtr<CanvasDrawingSession> CreateNew(
            ID2D1DeviceContext1* deviceContext,
            std::shared_ptr<ICanvasDrawingSessionAdapter> drawingSessionAdapter);

        ComPtr<CanvasDrawingSession> CreateWrapper(
            ID2D1DeviceContext1* resource);
    };
}