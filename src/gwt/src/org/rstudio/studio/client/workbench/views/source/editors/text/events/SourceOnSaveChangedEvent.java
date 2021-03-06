/*
 * SourceOnSaveChangedEvent.java
 *
 * Copyright (C) 2009-11 by RStudio, Inc.
 *
 * This program is licensed to you under the terms of version 3 of the
 * GNU Affero General Public License. This program is distributed WITHOUT
 * ANY EXPRESS OR IMPLIED WARRANTY, INCLUDING THOSE OF NON-INFRINGEMENT,
 * MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE. Please refer to the
 * AGPL (http://www.gnu.org/licenses/agpl-3.0.txt) for more details.
 *
 */
package org.rstudio.studio.client.workbench.views.source.editors.text.events;

import com.google.gwt.event.shared.GwtEvent;

public class SourceOnSaveChangedEvent extends GwtEvent<SourceOnSaveChangedHandler>
{
   public static final Type<SourceOnSaveChangedHandler> TYPE = new Type<SourceOnSaveChangedHandler>();

   @Override
   public Type<SourceOnSaveChangedHandler> getAssociatedType()
   {
      return TYPE;
   }

   @Override
   protected void dispatch(SourceOnSaveChangedHandler handler)
   {
      handler.onSourceOnSaveChanged(this);
   }
}
