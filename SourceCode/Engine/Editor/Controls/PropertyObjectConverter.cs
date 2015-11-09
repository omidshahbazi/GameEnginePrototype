// Copyright 2012-2015 ?????????????. All Rights Reserved.
using System;
using System.ComponentModel;
using System.Globalization;
using ManagedWrapper;

namespace IE.Controls
{
	class PropertyObjectConverter : ExpandableObjectConverter
	{
		public override bool CanConvertFrom(ITypeDescriptorContext Context, Type SourceType)
		{
			if (SourceType == typeof(string))
				return true;

			return base.CanConvertFrom(Context, SourceType);
		}

		public override bool CanConvertTo(ITypeDescriptorContext Context, Type DestinationType)
		{
			if (DestinationType == typeof(GPUProgram))
				return true;

			return base.CanConvertTo(Context, DestinationType);
		}

		public override object ConvertFrom(ITypeDescriptorContext Context, CultureInfo Culture, object Value)
		{
			if (Value is string)
			{
				string s = (string)Value;
				int colon = s.IndexOf(':');
				int comma = s.IndexOf(',');

				if (colon != -1 && comma != -1)
				{
					string checkWhileTyping = s.Substring(colon + 1,
													(comma - colon - 1));

					colon = s.IndexOf(':', comma + 1);
					comma = s.IndexOf(',', comma + 1);

					string checkCaps = s.Substring(colon + 1,
													(comma - colon - 1));

					colon = s.IndexOf(':', comma + 1);

					string suggCorr = s.Substring(colon + 1);

					//GPUProgram so = new GPUProgram();

					//so.SpellCheckWhileTyping = Boolean.Parse(checkWhileTyping);
					//so.SpellCheckCAPS = Boolean.Parse(checkCaps);
					//so.SuggestCorrections = Boolean.Parse(suggCorr);

					//return so;

					return null;
				}
			}
			return base.ConvertFrom(Context, Culture, Value);
		}

		public override object ConvertTo(ITypeDescriptorContext Context, CultureInfo Culture, object Value, Type DestinationType)
		{
			if (DestinationType == typeof(String) && Value is GPUProgram)
			{

				GPUProgram so = (GPUProgram)Value;

				return "Check while typing : " + so.Pointer;
			}

			return base.ConvertTo(Context, Culture, Value, DestinationType);
		}
	}
}
